/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:42:59 by qang              #+#    #+#             */
/*   Updated: 2024/07/03 21:01:08 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

static int	skip_space_and_sign(char *str, long *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	ft_print_error(char *str)
{
	printf("exit: %s: numeric argument required\n", str);
	return (2);
}

static long	ft_exitatol(char *str)
{
	int		i;
	long	nbr;
	long	temp;
	long	sign;

	nbr = 0;
	sign = 1;
	i = skip_space_and_sign(str, &sign);
	while (str[i])
	{
		temp = nbr;
		if (!ft_isdigit(str[i]))
			return (ft_print_error(str));
		if (temp == LONG_MAX / 10 && str[i] == '8'
			&& sign == -1 && !ft_isdigit(str[i + 1]))
			return (LONG_MIN);
		nbr = nbr * 10 + str[i++] - '0';
		if (nbr / 10 != temp)
			return (ft_print_error(str));
	}
	return (nbr * sign);
}

static bool	is_valid(char *str)
{
	int		i;
	long	nbr;
	long	sign;

	nbr = 0;
	i = skip_space_and_sign(str, &sign);
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (false);
	}
	return (true);
}

int	exit_sh(char **arg, t_entab *table)
{
	printf("exit\n");
	if (length(arg) == 1)
	{
		free_env(table);
		exit(0);
	}
	if (length(arg) == 2)
		return (ft_exitatol(arg[1]) % 256);
	else
	{
		if (!is_valid(arg[1]))
			printf("exit: %s: numeric argument required\n", arg[1]);
		else
			printf("exit: too many arguments\n");
		return (2);
	}
	return (0);
}
