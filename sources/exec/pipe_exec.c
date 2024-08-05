/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:47:00 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 15:12:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "tree.h"
#include <unistd.h>

static void	pipe_write(t_Pipe_Node *node, int fd[2])
{
	dup2(fd[1], STDOUT_FILENO);
	close_pipe(fd);
	exec_ast(node->left);
	exit(get_exit_status());
}

static void	pipe_read(t_Pipe_Node *node, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close_pipe(fd);
	exec_ast(node->right);
	exit(get_exit_status());
}

void	paip(t_Pipe_Node *node)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pipepromax(fd);
	pid1 = forkpromax();
	if (pid1 == 0)
		pipe_write(node, fd);
	else
		ignore_sigs();
	set_exit_status(wait_for_child(pid1));
	if (get_exit_status() == 130)
	{
		close_pipe(fd);
		return ;
	}
	pid2 = forkpromax();
	if (pid2 == 0)
		pipe_read(node, fd);
	else
		ignore_sigs();
	close_pipe(fd);
	set_exit_status(wait_for_child(pid1));
	set_exit_status(wait_for_child(pid2));
}
