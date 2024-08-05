/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:42:59 by qang              #+#    #+#             */
/*   Updated: 2024/08/06 00:26:42 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "ft_dprintf.h"
#include <stdlib.h>

int			exit_sh(char **arg, t_entab *table);
static bool	is_valid(char *str);
static int	ft_print_error(char *str, bool *valid);
static int	skip_space_and_sign(char *str, long *sign);
static long	ft_exitatol(char *str, bool *valid);

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

static int	ft_print_error(char *str, bool *valid)
{
	*valid = false;
	ft_dprintf(2, "%s: exit: %s: numeric argument required\n", SHELL, str);
	return (2);
}

static long	ft_exitatol(char *str, bool *valid)
{
	int		i;
	long	nbr;
	long	temp;
	long	sign;

	nbr = 0;
	sign = 1;
	if (ft_strlen(str) > 20 || ft_strlen(str) == 0)
		return (ft_print_error(str, valid));
	i = skip_space_and_sign(str, &sign);
	while (str[i])
	{
		temp = nbr;
		if (!ft_isdigit(str[i]))
			return (ft_print_error(str, valid));
		if (temp == LONG_MAX / 10 && str[i] == '8'
			&& sign == -1 && !ft_isdigit(str[i + 1]))
			return (LONG_MIN);
		nbr = nbr * 10 + str[i++] - '0';
		if (nbr / 10 != temp)
			return (ft_print_error(str, valid));
	}
	return (nbr * sign);
}

static bool	is_valid(char *str)
{
	int		i;
	long	sign;

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
	bool	valid;

	valid = true;
	(void)table;
	ft_dprintf(2, "exit\n");
	if (length(arg) == 1)
		exit(get_exit_status());
	if (length(arg) == 2)
	{
		ft_exitatol(arg[1], &valid);
		if (!valid)
			return (2);
		exit(ft_exitatol(arg[1], &valid) % 256);
	}
	else
	{
		if (!is_valid(arg[1]))
			ft_dprintf(2, "%s: exit: %s: numeric argument required\n",
				SHELL, arg[1]);
		else
			ft_dprintf(2, "%s: exit: too many arguments\n", SHELL);
		return (2);
	}
	return (0);
}
