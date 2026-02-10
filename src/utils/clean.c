/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:23:38 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/10 01:13:50 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_rule(t_rules *rule)
{
	free(rule->dongle_locks);
	free(rule->dongle_cool_times);
	free(rule->dongle_status);
	free(rule->queue);
	free(rule->coders);
}

void	destroy_mutexes(t_rules *r)
{
	int i;

	i = 0;
	while (i < r->num_coders)
	{
		pthread_mutex_destroy(&r->dongle_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&r->global_lock);
	pthread_cond_destroy(&r->cond);
}
