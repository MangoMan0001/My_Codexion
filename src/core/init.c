/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:03:18 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/06 22:58:18 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init(t_rules *rule, int argc, char **argv)
{
	validate(argc, argv);
	rule->num_coders = atoi(argv[1]);
	rule->time_to_burnout = atoi(argv[2]);
	rule->time_to_compile = atoi(argv[3]);
	rule->time_to_debug = atoi(argv[4]);
	rule->time_to_refactor = atoi(argv[5]);
	rule->must_compile_count = atoi(argv[6]);
	rule->dongle_cooldown = atoi(argv[7]);
	if (!strcmp(argv[8], "fifo"))
		rule->scheduler_typy = FIFO;
	else if (!strcmp(argv[8], "edf"))
		rule->scheduler_typy = EDF;
	printf("%d", rule->num_coders);
	printf("%lld", rule->time_to_burnout);
	printf("%lld", rule->time_to_compile);
	printf("%lld", rule->time_to_debug);
	printf("%lld", rule->time_to_refactor);
	printf("%d", rule->must_compile_count);
	printf("%d", rule->dongle_cooldown);
	printf("%d", rule->scheduler_typy);
}
