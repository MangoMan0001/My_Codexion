/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:52:49 by ayhirose          #+#    #+#             */
/*   Updated: 2026/03/03 02:19:56 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Function for thread branching
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
			pthread_mutex_lock(&rule->global_lock);
			rule->is_simulation_active = FALSE;
			pthread_mutex_unlock(&rule->global_lock);
			while (--i >= 0)
				pthread_join(rule->coders[i].tid, NULL);
			return (1);
		}
		i++;
	}
	if (pthread_create(&rule->monitor, NULL, monitor, rule))
	{
		pthread_mutex_lock(&rule->global_lock);
		rule->is_simulation_active = FALSE;
		pthread_mutex_unlock(&rule->global_lock);
		while (--i >= 0)
			pthread_join(rule->coders[i].tid, NULL);
		return (1);
	}
	return (0);
}

// Function waiting for thread integration
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

// Tread Branching Control Function
int	simulation(t_rules *rules)
{
	if (create_threads(rules))
		return (1);
	join_threads(rules);
	return (0);
}
