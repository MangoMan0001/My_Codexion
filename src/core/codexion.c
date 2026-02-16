/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:23:25 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/16 17:13:21 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	codexion(int argc, char **argv)
{
	t_rules	rule;

	if (init(&rule, argc, argv))
		return (1);
	simulation(&rule);
	destroy_mutexes(&rule);
	free_rule(&rule);
	return (0);
}
