/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:42:10 by qang              #+#    #+#             */
/*   Updated: 2024/08/03 01:17:37 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "tree.h"
#include <stdbool.h>
#include <unistd.h>

#include <fcntl.h>
#include <stdio.h>

bool	left_is_builtin(t_Pipe_Node *node)
{
	if (node->left->type == EXEC_NODE && ft_isbuiltin(((t_Exec_Node *)(node->left))->command))
		return (true);
	return (false);
}

void	paip_helper(t_Pipe_Node *node)
{
	int	fd[2];
	int	temp_fd[2];
	int	pid1;

	temp_fd[0] = dup(STDIN_FILENO);
	temp_fd[1] = dup(STDOUT_FILENO);
	pipepromax(fd);
	pid1 = forkpromax();
	if (pid1 > 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		close(temp_fd[0]);
		exec_ast(node->left);
		dup2(temp_fd[1], STDOUT_FILENO);
		close(temp_fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		close_pipe(temp_fd);
		exec_ast(node->right);
		exit(get_exit_status());
	}
	set_exit_status(wait_for_child(pid1));
}