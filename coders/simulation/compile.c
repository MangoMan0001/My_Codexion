/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 22:21:18 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/16 18:42:45 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	can_i_get_the_usb(t_coder *coder, t_rules *rule, int *flag)
{
	int			l_usb;
	int			r_usb;
	int			*status;
	long long	*cool_times;
	long long	now;

	*flag = rule->is_simulation_active;
	if (*flag == FALSE)
		return (TRUE);
	l_usb = coder->left_dongle_id;
	r_usb = coder->right_dongle_id;
	status = rule->dongle_status;
	cool_times = rule->dongle_cool_times;
	if (scheduler(coder) == FALSE)
		return (FALSE);
	if (status[l_usb] || status[r_usb])
		return (FALSE);
	now = get_time();
	if (now < cool_times[l_usb] || now < cool_times[r_usb])
		return (FALSE);
	return (TRUE);
}

static void	just_compiling(t_coder *coder, t_rules *rule)
{
	int			first;
	int			second;

	first = coder->left_dongle_id;
	second = coder->right_dongle_id;
	if (coder->right_coder_id < coder->left_coder_id)
	{
		first = coder->right_dongle_id;
		second = coder->left_dongle_id;
	}
	pthread_mutex_lock(&rule->dongle_locks[first]);
	print_log_lock(coder, "has taken a dongle");
	if (first == second)
	{
		while (just_sleep(50, rule))
			continue ;
		pthread_mutex_unlock(&rule->dongle_locks[first]);
		return ;
	}
	pthread_mutex_lock(&rule->dongle_locks[second]);
	print_log_lock(coder, "has taken a dongle");
	print_log_lock(coder, "is compiling");
	just_sleep(rule->time_to_compile, rule);
	pthread_mutex_unlock(&rule->dongle_locks[first]);
	pthread_mutex_unlock(&rule->dongle_locks[second]);
}

static void	reserve_usb(t_coder *coder)
{
	t_rules		*rule;

	rule = coder->rule;
	rule->dongle_status[coder->left_dongle_id] = TRUE;
	rule->dongle_status[coder->right_dongle_id] = TRUE;
	pop_queue(coder);
	coder->last_compile_start = get_time();
}

static void	return_usb(t_coder *coder)
{
	t_rules		*rule;
	long long	time;

	rule = coder->rule;
	rule->dongle_status[coder->left_dongle_id] = FALSE;
	rule->dongle_status[coder->right_dongle_id] = FALSE;
	time = rule->dongle_cooldown + get_time();
	rule->dongle_cool_times[coder->left_dongle_id] = time;
	rule->dongle_cool_times[coder->right_dongle_id] = time;
	coder->compile_count++;
}

void	routine_compile(t_coder *coder, int *flag)
{
	t_rules		*rule;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	while (can_i_get_the_usb(coder, rule, flag) == FALSE)
		pthread_cond_wait(&rule->cond, &rule->global_lock);
	if (*flag)
	{
		reserve_usb(coder);
		pthread_mutex_unlock(&rule->global_lock);
		just_compiling(coder, rule);
		pthread_mutex_lock(&rule->global_lock);
		return_usb(coder);
		pthread_cond_broadcast(&rule->cond);
	}
	pthread_mutex_unlock(&rule->global_lock);
}
