/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:32:05 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/11 07:52:23 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	routine_refactoring(t_coder *coder, int *flag)
{
	t_rules 	*rule;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	*flag = rule->is_simulation_active;
	if (*flag)
		print_log(coder, "is refactoring");
	pthread_mutex_unlock(&rule->global_lock);
	just_sleep(rule->time_to_refactor, rule);
}

static void	routine_debug(t_coder *coder, int *flag)
{
	t_rules 	*rule;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	*flag = rule->is_simulation_active;
	if (*flag)
		print_log(coder, "is debugging");
	pthread_mutex_unlock(&rule->global_lock);
	just_sleep(rule->time_to_debug, rule);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	int		flag;

	coder = (t_coder *)arg;
	flag = TRUE;
	while (flag)
	{
		routine_compile(coder, &flag);
		routine_debug(coder, &flag);
		routine_refactoring(coder, &flag);
	}
	return (NULL);
}
