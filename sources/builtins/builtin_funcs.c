/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:35:04 by qang              #+#    #+#             */
/*   Updated: 2024/07/06 00:59:24 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include "libft.h"

int	length(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	run_builtin(const char **cav, t_entab *table)
{
	int		errno;
	char	**av;

	av = (char **)cav;
	errno = 0;
	if (ft_strcmp("echo", av[0]) == 0)
		errno = echo(av);
	else if (ft_strcmp("cd", av[0]) == 0)
		errno = cd(av, table);
	else if (ft_strcmp("pwd", av[0]) == 0)
		errno = pwd(av, table);
	else if (ft_strcmp("export", av[0]) == 0)
		errno = export(av, table);
	else if (ft_strcmp("unset", av[0]) == 0)
		errno = unset(av, table);
	else if (ft_strcmp("env", av[0]) == 0)
		errno = print_env(av, table);
	else if (ft_strcmp("exit", av[0]) == 0)
		errno = exit_sh(av, table);
	return (errno);
}

bool	ft_isbuiltin(const char *command)
{
	return (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "exit") == 0);
}
