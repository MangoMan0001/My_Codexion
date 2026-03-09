/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:02:33 by ayhirose          #+#    #+#             */
/*   Updated: 2026/03/08 09:18:18 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Reimplementation of calloc
void	*my_calloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (NULL);
	return (memset(result, 0, size));
}

// Output the log
void	print_log(t_coder *coder, long long now_us, char *msg)
{
	long long	log_msg;

	log_msg = (now_us - coder->rule->start_time) / 1000;
	printf("%lld %d %s\n", log_msg, coder->id, msg);
}

// Output the log after acquiring mutex protection
void	print_log_lock(t_coder *coder, long long now_us, char *msg)
{
	pthread_mutex_lock(&coder->rule->global_lock);
	if (coder->rule->is_simulation_active)
		print_log(coder, now_us, msg);
	pthread_mutex_unlock(&coder->rule->global_lock);
}
