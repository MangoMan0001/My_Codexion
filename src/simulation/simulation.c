/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:52:49 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/09 23:27:28 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	create_threads(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->num_coders)
	{
		rules->coders[i].last_compile_start = rules->start_time;
		if (pthread_create(&rules->coders[i].tid, NULL, routine, &rules->coders[i]))
		{
			rules->is_simulation_active = FALSE;
			while (--i >= 0)
				pthread_join(rules->coders[i].tid, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_coders)
	{
		pthread_join(rules->coders[i].tid, NULL);
		i++;
	}
}

int	simulation(t_rules *rules)
{
	if (create_threads(rules))
		return (1);

	join_threads(rules);

	return (0);
}
