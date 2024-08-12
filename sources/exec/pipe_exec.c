/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:47:00 by qang              #+#    #+#             */
/*   Updated: 2024/08/12 23:27:56 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "tree.h"
#include <signal.h>
#include <unistd.h>

static void	pipe_write(t_Pipe_Node *node, int fd[2])
{
	default_sigs();
	dup2(fd[1], STDOUT_FILENO);
	close_pipe(fd);
	exec_ast(node->left);
	exit(get_exit_status());
}

static void	pipe_read(t_Pipe_Node *node, int fd[2])
{
	default_sigs();
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

	ignore_sigs();
	pipepromax(fd);
	pid1 = forkpromax();
	if (pid1 == 0)
		pipe_write(node, fd);
	pid2 = forkpromax();
	if (pid2 == 0)
		pipe_read(node, fd);
	close_pipe(fd);
	set_exit_status(wait_for_child(pid1));
	set_exit_status(wait_for_child(pid2));
}
