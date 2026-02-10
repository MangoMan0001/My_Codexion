/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:02:33 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/10 01:51:06 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*my_calloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return NULL;
	return memset(result, 0, size);
}
