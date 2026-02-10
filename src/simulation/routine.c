/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:32:05 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/10 04:49:35 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	routine_refactoring(t_coder *coder, int *flag)
{
	t_rules 	*rule;
	long long	time;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	*flag = rule->is_simulation_active;
	if (*flag)
	{
		time = get_time() - rule->start_time;
		printf("%lld %d is refactoring\n", time, coder->id);
	}
	pthread_mutex_unlock(&rule->global_lock);
	just_sleep(rule->time_to_refactor, rule);
}

static void	routine_debug(t_coder *coder, int *flag)
{
	t_rules 	*rule;
	long long	time;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	*flag = rule->is_simulation_active;
	if (*flag)
	{
		time = get_time() - rule->start_time;
		printf("%lld %d is debugging\n", time, coder->id);
	}
	pthread_mutex_unlock(&rule->global_lock);
	just_sleep(rule->time_to_debug, rule);
}

static int	can_i_get_the_usb(t_coder *coder, t_rules *rule)
{
	int			flag;
	int			l_usb;
	int			r_usb;
	int			*status;
	long long	*cool_times;

	flag = 0;
	l_usb = coder->left_dongle_id;
	r_usb = coder->right_dongle_id;
	status = rule->dongle_status;
	cool_times = rule->dongle_cool_times;
	if (scheduler(coder) == FALSE) // 自分が両隣のコーダーより優先か
		flag = 1;
	if (status[l_usb] && status[r_usb]) // 両隣のUSBが机の上に置いてあるか
		flag = 1;
	if (cool_times[l_usb] && cool_times[r_usb]) // 両隣のUSBのクールダウンが終わってるか
		flag = 1;

	return flag;
}

static void	routine_compile(t_coder *coder, int *flag)
{
	t_rules	*rule;

	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	while (can_i_get_the_usb(coder, rule))
	{

	}
	pthread_mutex_unlock(&rule->global_lock);
	pop_queue(coder);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	int		flag;

	coder = (t_coder *)arg;
	flag = TRUE;
	while (flag)
	{
		routine_compile(coder, &flag);
		routine_debug(coder, &flag);
		routine_refactoring(coder, &flag);
	}

	return (NULL);
}
