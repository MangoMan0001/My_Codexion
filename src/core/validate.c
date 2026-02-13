/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:03:15 by ayhirose          #+#    #+#             */
/*   Updated: 2026/02/13 18:49:53 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_digit(char c)
{
	if (!('0' <= c && c <= '9'))
		return 1;
	return 0;
}

static int	is_int(char *str)
{
	int		i;
	long 	num;

	i = 0;
	num = 0;
	if (!str || !str[i])
		return 1;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return 1;
	while (str[i])
	{
		if (is_digit(str[i]))
			return 1;
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return 1;
		i++;
	}
	return 0;
}

int	validate(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 9)
	{
		fprintf(stderr, "must be eight arguments..\n");
		return 1;
	}
	while (i < 8)
	{
		if (is_int(argv[i]))
		{
			fprintf(stderr, "Arguments 1~7 are numbers only.\n");
			return 1;
		}
		i++;
	}
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
	{
		fprintf(stderr, "8 argument is only for 'fifo' and 'edf'.\n");
		return 1;
	}
	return 0;
}
