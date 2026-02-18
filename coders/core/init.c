/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:03:18 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/18 16:40:37 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// すべての動的メモリ確保をまとめて行う
static int	init_malloc(t_rules *rule)
{
	rule->dongle_locks = (pthread_mutex_t *)my_calloc(sizeof(pthread_mutex_t) * \
														rule->num_coders);
	rule->dongle_cool_times = (long long *)my_calloc(sizeof(long long) * \
														rule->num_coders);
	rule->dongle_status = (int *)my_calloc(sizeof(int) * rule->num_coders);
	rule->queue = (int *)my_calloc(sizeof(int) * (rule->num_coders + 1));
	rule->coders = (t_coder *)my_calloc(sizeof(t_coder) * rule->num_coders);
	if (!rule->coders || !rule->dongle_locks || !rule->dongle_cool_times \
		|| !rule->dongle_status || !rule->queue)
		return (1);
	return (0);
}

// pthreadのリソース確保
static int	init_pthread(t_rules *rule)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&rule->global_lock, NULL))
		return (1);
	if (pthread_cond_init(&rule->cond, NULL))
	{
		pthread_mutex_destroy(&rule->global_lock);
		return (1);
	}
	while (i < rule->num_coders)
	{
		if (pthread_mutex_init(&rule->dongle_locks[i], NULL))
		{
			while (0 <= --i)
				pthread_mutex_destroy(&rule->dongle_locks[i]);
			pthread_mutex_destroy(&rule->global_lock);
			pthread_cond_destroy(&rule->cond);
			return (1);
		}
		i++;
	}
	return (0);
}

// rule構造体の初期化
static int	init_rule(t_rules *rule, char **argv)
{
	memset(rule, 0, sizeof(t_rules));
	rule->num_coders = atoi(argv[1]);
	rule->time_to_burnout = atoi(argv[2]);
	rule->time_to_compile = atoi(argv[3]);
	rule->time_to_debug = atoi(argv[4]);
	rule->time_to_refactor = atoi(argv[5]);
	rule->must_compile_count = atoi(argv[6]);
	rule->dongle_cooldown = atoi(argv[7]);
	rule->is_simulation_active = TRUE;
	if (!strcmp(argv[8], "fifo"))
		rule->scheduler_type = FIFO;
	else if (!strcmp(argv[8], "edf"))
		rule->scheduler_type = EDF;
	if (init_malloc(rule))
		return (1);
	if (init_pthread(rule))
		return (1);
	return (0);
}

// coder構造体の初期化
static void	init_coder(t_rules *rule)
{
	int	i;

	i = 0;
	while (i < rule->num_coders)
	{
		rule->coders[i].id = i + 1;
		rule->coders[i].left_coder_id = (i + rule->num_coders - 1) % \
										rule->num_coders + 1;
		rule->coders[i].right_coder_id = (i + 1) % rule->num_coders + 1;
		rule->coders[i].left_dongle_id = i;
		rule->coders[i].right_dongle_id = (i + 1) % rule->num_coders;
		rule->coders[i].rule = rule;
		i++;
	}
}

// 初期化統括関数
int	init(t_rules *rule, int argc, char **argv)
{
	if (validate(argc, argv))
		return (1);
	if (init_rule(rule, argv))
	{
		free_rule(rule);
		return (1);
	}
	init_coder(rule);
	return (0);
}
