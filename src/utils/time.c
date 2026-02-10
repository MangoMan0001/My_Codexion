/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:42:06 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/09 23:51:11 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
** 現在時刻をミリ秒で返す
** 1970年1月1日からの経過ミリ秒です。
*/
long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
** 指定時間(ms)だけ眠る
** 負荷軽減のためusleep(50)刻みで確認
*/
void	just_sleep(long long time, t_rules *rule)
{
	long long	start;
	int			flag;

	flag = TRUE;
	start = get_time();
	while (flag)
	{
		if (get_time() - start >= time)
			break ;
		usleep(50);
		pthread_mutex_lock(&rule->global_lock);
		flag = rule->is_simulation_active;
		pthread_mutex_unlock(&rule->global_lock);
	}
}
