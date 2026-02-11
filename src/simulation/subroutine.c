/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:56:52 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/12 02:19:43 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// static void	is_dongle_cooldown(t_rules *rule)
// {
// 	int			i;
// 	long long	now;
// 	int			l_usb;
// 	int			r_usb;
// 	t_coder		coder;

// 	i = 0;
// 	if (rule->is_simulation_active)
// 		while (i < rule->num_coders)
// 		{
// 			coder = rule->coders[i];
// 			l_usb = coder.left_dongle_id;
// 			r_usb = coder.right_dongle_id;
// 			now = get_time();
// 			if (rule->dongle_cool_times[l_usb] < now  && \
// 				rule->dongle_cool_times[r_usb] < now)
// 				pthread_cond_broadcast(&rule->cond);
// 			i++;
// 		}
// }

static void	is_someone_burned_out(t_rules *rule)
{
	int			i;
	long long	time;

	i = 0;
	if (rule->is_simulation_active == FALSE)
		return ;
	while (i < rule->num_coders)
	{
		time = get_time() - rule->coders[i].last_compile_start;
		if (rule->time_to_burnout <= time)
		{
			print_log(&rule->coders[i], "burned out");
			rule->is_simulation_active = FALSE;
			return;
		}
		i++;
	}
}

static void	is_simulation_finished(t_rules *rule)
{
	int	i;

	i = 0;
	if (rule->is_simulation_active == FALSE || \
		rule->must_compile_count == -1)
		return ;
	while (i < rule->num_coders)
	{
		if (rule->coders[i].compile_count < rule->must_compile_count)
			return ;
		i++;
	}
	printf("simulation finish");
	rule->is_simulation_active = FALSE;
}

void	*monitor(void *arg)
{
	t_rules	*rule;

	rule = (t_rules *)arg;
	while (TRUE)
	{
		pthread_mutex_lock(&rule->global_lock);
		if (rule->is_simulation_active == FALSE)
		{
			pthread_mutex_unlock(&rule->global_lock);
			break;
		}
		is_simulation_finished(rule);
		is_someone_burned_out(rule);
		// is_dongle_cooldown(rule);
		pthread_cond_broadcast(&rule->cond);
		pthread_mutex_unlock(&rule->global_lock);
		usleep(1000);
	}
	return NULL;
}
