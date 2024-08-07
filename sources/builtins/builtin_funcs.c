/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:35:04 by qang              #+#    #+#             */
/*   Updated: 2024/08/07 17:01:26 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "execution.h"
#include "libft.h"
#include <stdbool.h>

bool	ft_isbuiltin(const char *command);
int		length(char **arg);
int		run_builtin(const char **cav, t_entab *table);

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
	if (ft_strcmp2("echo", av[0]) == 0)
		errno = echo(av);
	else if (ft_strcmp2("cd", av[0]) == 0)
		errno = cd(av, table);
	else if (ft_strcmp2("pwd", av[0]) == 0)
		errno = pwd(av, table);
	else if (ft_strcmp2("export", av[0]) == 0)
		errno = ft_export(av, table);
	else if (ft_strcmp2("unset", av[0]) == 0)
		errno = unset(av, table);
	else if (ft_strcmp2("env", av[0]) == 0)
		errno = print_env(av, table);
	else if (ft_strcmp2("exit", av[0]) == 0)
		errno = exit_sh(av, table);
	return (errno);
}

bool	ft_isbuiltin(const char *command)
{
	return (ft_strcmp2(command, "echo") == 0 || ft_strcmp2(command, "cd") == 0
		|| ft_strcmp2(command, "pwd") == 0 || ft_strcmp(command, "export") == 0
		|| ft_strcmp2(command, "unset") == 0 || ft_strcmp2(command, "env") == 0
		|| ft_strcmp(command, "exit") == 0);
}
