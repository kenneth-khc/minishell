/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:48:55 by qang              #+#    #+#             */
/*   Updated: 2024/07/13 00:55:54 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	child_process(t_Exec_Node *node, t_entab *table)
{
	set_sig();
	if (!ft_isbuiltin(node->command))
	{
		if (access(node->command, F_OK) == 0
			&& access(node->command, X_OK) == 0)
			execve((char *)node->command, (char **)node->args,
				env_convert(table));
		execvepromax((char **)node->args, table, get_var("PATH", table));
		ft_dprintf(2, "%s: %s: command not found\n", SHELL, node->command);
	}
	exit(0);
}

void	exec(t_Exec_Node *node)
{
	int	pid;

	pid = forkpromax();
	if (pid == 0)
		child_process(node, node->table);
	else
	{
		ignore_sigs();
		if (ft_isbuiltin(node->command))
			set_exit_status(run_builtin(node->args, node->table));
	}
	if (!ft_isbuiltin(node->command))
		set_exit_status(wait_for_child(pid));
}
