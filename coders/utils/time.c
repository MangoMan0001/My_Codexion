/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:42:06 by ayhirose          #+#    #+#             */
/*   Updated: 2026/03/10 11:39:46 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** Returns the current time in microseconds (μs)
** This is the number of microseconds elapsed since January 1, 1970.
*/
long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	return ((tv.tv_sec * 1000000LL) + tv.tv_usec);
}

/*
** Sleep for the specified duration (μs)
** Check in increments of usleep(50) to reduce load
*/
int	just_sleep(long long time, t_rules *rule)
{
	long long	start;
	int			flag;

	flag = TRUE;
	start = get_time();
	while (flag)
	{
		if (time <= get_time() - start)
			return (1);
		usleep(50);
		pthread_mutex_lock(&rule->global_lock);
		flag = rule->is_simulation_active;
		pthread_mutex_unlock(&rule->global_lock);
	}
	return (0);
}
