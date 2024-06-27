/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:42:59 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 21:23:28 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

static int	ft_exitatoi(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
		{
			printf("exit: %s: numeric argument required\n", str);
			return (2);
		}
	}
	return (ft_atoi(&str[i]));
}

int	exit_sh(char **arg, t_entab *table)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (length(arg) == 1)
	{
		free_env(table);
		exit(ft_atoi(arg[0]));
	}
	if (length(arg) == 2)
		ft_exitatoi(arg[1]);
	else
	{
		if (ft_exitatoi(arg[1]) == 2)
			return (2);
		printf("exit: too many arguments\n");
		return (2);
	}
	return (0);
}
