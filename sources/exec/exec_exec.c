/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:48:55 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 16:29:10 by codespace        ###   ########.fr       */
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
	default_sigs();
	if (!ft_isbuiltin(node->command))
	{
		check_file(node->command, node->command);
		if (access(node->command, F_OK) == 0
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
	int		pid;
	char	*temp;

	temp = ft_strjoin("_=", node->args[length((char **)node->args) - 1]);
	add_var(temp, node->table);
	free(temp);
	pid = forkpromax();
	if (pid == 0)
		child_process(node, node->table);
	else
	{
		ignore_sigs();
		if (ft_isbuiltin(node->command))
			set_exit_status(run_builtin(node->args, node->table));
		else
			set_exit_status(wait_for_child(pid));
	}
}
