/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:23:38 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/18 16:35:13 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// メモリ開放
void	free_rule(t_rules *rule)
{
	free(rule->dongle_locks);
	free(rule->dongle_cool_times);
	free(rule->dongle_status);
	free(rule->queue);
	free(rule->coders);
}

// Mutexとcondのリソースを開放する
void	destroy_mutexes(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_coders)
	{
		pthread_mutex_destroy(&r->dongle_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&r->global_lock);
	pthread_cond_destroy(&r->cond);
}
