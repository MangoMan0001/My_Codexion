/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subroutine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:56:52 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/18 16:57:45 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// 燃え尽きが発生したかを確認する関数
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
			return ;
		}
		i++;
	}
}

// シミュレーションが終了したかを確認する関数
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
	printf("simulation finish\n");
	rule->is_simulation_active = FALSE;
}

// Monitor thread entry point.
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
			break ;
		}
		is_simulation_finished(rule);
		is_someone_burned_out(rule);
		pthread_cond_broadcast(&rule->cond);
		pthread_mutex_unlock(&rule->global_lock);
		usleep(1000);
	}
	return (NULL);
}
