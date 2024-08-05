/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:48:55 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 15:11:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "execution.h"
#include "ft_dprintf.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void	child_process(t_Exec_Node *node, t_entab *table);
void	exec(t_Exec_Node *node);

void	child_process(t_Exec_Node *node, t_entab *table)
{
	struct stat	file_stats;

	default_sigs();
	if (!ft_isbuiltin(node->command))
	{
		if (stat(node->command, &file_stats) == 0
			&& S_ISDIR(file_stats.st_mode))
		{
			ft_dprintf(2, "%s: %s: is a directory\n", SHELL, node->command);
			exit(126);
		}
		else if (access(node->command, F_OK) == 0
			&& access(node->command, X_OK) == 0)
			execve((char *)node->command, (char **)node->args,
				env_convert(table));
		else
		{
			execvepromax((char **)node->args, table, get_var("PATH", table));
			ft_dprintf(2, "%s: %s: command not found\n", SHELL, node->command);
			exit(127);
		}
	}
	exit(0);
}

void	exec(t_Exec_Node *node)
{
	int	pid;

	pid = forkpromax();
	if (pid == 0)
	{
		if (ft_strcmp(node->command, ".") == 0)
		{
			ft_dprintf(2, "%s: .: filename argument required\n", SHELL);
			exit(2);
		}
		if (ft_strcmp(node->command, "..") == 0)
		{
			ft_dprintf(2, "%s: ..: command not found\n", SHELL);
			exit(127);
		}
		child_process(node, node->table);
	}
	else
	{
		ignore_sigs();
		if (ft_isbuiltin(node->command))
			set_exit_status(run_builtin(node->args, node->table));
		else
			set_exit_status(wait_for_child(pid));
	}
}
