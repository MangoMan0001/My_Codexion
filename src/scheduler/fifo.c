/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:49:55 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/10 04:51:30 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	pop_queue(t_coder *coder)
{
	t_rules	*rule;
	int		tail;
	int		prev_id;
	int		current_id;

	rule = coder->rule;
	tail = rule->queue_size;
	prev_id = rule->queue[tail];
	while (0 <= tail)
	{
		current_id = rule->queue[tail];
		rule->queue[tail] = prev_id;
		if (current_id == coder->id)
			break ;
		prev_id = current_id;
		tail--;
	}
	rule->queue_size--;
}

static int	first_out(t_coder *coder)
{
	t_rules	*rule;
	int		head;

	rule = coder->rule;
	head = 0;
	while (head < rule->queue_size)
	{
		if (rule->queue[head] == coder->left_coder_id || \
			rule->queue[head] == coder->right_coder_id)
			return FALSE;
		if (rule->queue[head] == coder->id)
			break ;
		head++;
	}
	return TRUE;
}

static void	first_in(t_coder *coder)
{
	t_rules	*rule;
	int		head;

	rule = coder->rule;
	head = 0;
	while (head < rule->queue_size)
	{
		if (rule->queue[head] == coder->id)
			return ;
		head++;
	}
	rule->queue[rule->queue_size] = coder->id;
	rule->queue_size++;
}

int	fifo(t_coder *coder)
{
	first_in(coder);
	return first_out(coder);
}
