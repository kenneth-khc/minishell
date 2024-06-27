/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:35:04 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 22:28:44 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

int	length(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	run_builtin(char **av, t_entab *table)
{
	int	errno;

	errno = 0;
	if (ft_strcmp("echo", av[1]) == 0)
		errno = echo(&av[1]);
	else if (ft_strcmp("cd", av[1]) == 0)
		errno = cd(&av[1], table);
	else if (ft_strcmp("pwd", av[1]) == 0)
		errno = pwd(&av[1], table);
	else if (ft_strcmp("export", av[1]) == 0)
		errno = export(&av[1], table);
	else if (ft_strcmp("unset", av[1]) == 0)
		errno = unset(&av[1], table);
	else if (ft_strcmp("env", av[1]) == 0)
		errno = print_env(&av[1], table);
	else if (ft_strcmp("exit", av[1]) == 0)
		errno = exit_sh(&av[1], table);
	return (errno);
}

bool	ft_isbuiltin(char **av)
{
	if (ft_strcmp(av[0], "echo") == 0 || ft_strcmp(av[0], "cd") == 0
		|| ft_strcmp(av[0], "pwd") == 0 || ft_strcmp(av[0], "export") == 0
		|| ft_strcmp(av[0], "unset") == 0 || ft_strcmp(av[0], "env") == 0
		|| ft_strcmp(av[0], "exit") == 0)
		return (true);
	return (false);
}
