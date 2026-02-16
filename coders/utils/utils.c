/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:02:33 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/16 17:38:46 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*my_calloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (NULL);
	return (memset(result, 0, size));
}

void	print_log(t_coder *coder, char *msg)
{
	long long	time;
	t_rules		*rule;

	rule = coder->rule;
	time = get_time() - rule->start_time;
	printf("%lld %d %s\n", time, coder->id, msg);
}

void	print_log_lock(t_coder *coder, char *msg)
{
	long long	time;
	t_rules		*rule;

	rule = coder->rule;
	pthread_mutex_lock(&rule->global_lock);
	if (rule->is_simulation_active)
	{
		time = get_time() - rule->start_time;
		printf("%lld %d %s\n", time, coder->id, msg);
	}
	pthread_mutex_unlock(&rule->global_lock);
}
