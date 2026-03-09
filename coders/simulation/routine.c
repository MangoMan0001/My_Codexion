/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:32:05 by ayhirose          #+#    #+#             */
/*   Updated: 2026/03/08 09:17:25 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Refactoring Function
static void	routine_refactoring(t_coder *coder, int *flag)
{
	t_rules	*rule;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	*flag = rule->is_simulation_active;
	if (*flag)
		print_log(coder, get_time(), "is refactoring");
	pthread_mutex_unlock(&rule->global_lock);
	just_sleep(rule->time_to_refactor, rule);
}

// Debug Function
static void	routine_debug(t_coder *coder, int *flag)
{
	t_rules	*rule;

	if (!*flag)
		return ;
	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	*flag = rule->is_simulation_active;
	if (*flag)
		print_log(coder, get_time(), "is debugging");
	pthread_mutex_unlock(&rule->global_lock);
	just_sleep(rule->time_to_debug, rule);
}

// Coder_thread entry point.
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
