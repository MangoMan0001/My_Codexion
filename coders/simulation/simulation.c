/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:52:49 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/18 16:54:06 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// threadの分岐を行う関数
static int	create_threads(t_rules *rule)
{
	int	i;

	i = 0;
	rule->start_time = get_time();
	while (i < rule->num_coders)
	{
		rule->coders[i].last_compile_start = rule->start_time;
		if (pthread_create(&rule->coders[i].tid, NULL, \
							routine, &rule->coders[i]))
		{
			rule->is_simulation_active = FALSE;
			while (--i >= 0)
				pthread_join(rule->coders[i].tid, NULL);
			return (1);
		}
		i++;
	}
	if (pthread_create(&rule->monitor, NULL, monitor, rule))
		return (1);
	return (0);
}

// threadの統合を待つ関数
static void	join_threads(t_rules *rule)
{
	int	i;

	i = 0;
	while (i < rule->num_coders)
	{
		pthread_join(rule->coders[i].tid, NULL);
		i++;
	}
	pthread_join(rule->monitor, NULL);
}

// thread分岐統括関数
int	simulation(t_rules *rules)
{
	if (create_threads(rules))
		return (1);
	join_threads(rules);
	return (0);
}
