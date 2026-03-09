/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:58:10 by ayhirose          #+#    #+#             */
/*   Updated: 2026/03/09 12:18:06 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Scheduler Control Function
int	scheduler(t_coder *coder)
{
	t_rules	*rule;
	t_coder	*l_coder;
	t_coder	*r_coder;

	rule = coder->rule;
	l_coder = &rule->coders[coder->left_coder_id - 1];
	r_coder = &rule->coders[coder->right_coder_id - 1];
	if (coder->is_in_queue == FALSE)
	{
		rule->queue_size++;
		rule->queue[rule->queue_size] = coder->id;
		coder->is_in_queue = TRUE;
		coder->enqueue_time = get_time();
		shift_up(rule->queue_size, rule);
	}
	if (l_coder->is_in_queue && \
		compare_coders(coder->id, coder->left_coder_id, rule) == FALSE)
		return (FALSE);
	if (r_coder->is_in_queue && \
		compare_coders(coder->id, coder->right_coder_id, rule) == FALSE)
		return (FALSE);
	return (TRUE);
}
