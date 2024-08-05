/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:47:00 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 12:25:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "tree.h"
#include <unistd.h>

static void	pipe_child_process(t_Pipe_Node *node, int fd[2])
{
	int	pid;

	pid = forkpromax();
	if (pid == 0)
	{
		default_sigs();
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		exec_ast(node->left);
		exit(get_exit_status());
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid));
	}
}

static void	papi(t_Pipe_Node *node, int fd[2])
{
	int	pid;

	pid = forkpromax();
	if (pid == 0)
	{
		default_sigs();
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		exec_ast(node->right);
		exit(get_exit_status());
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid));
	}
}

void	paip(t_Pipe_Node *node)
{
	int	fd[2];

	pipepromax(fd);
	pipe_child_process(node, fd);
	if (get_exit_status() == 130)
	{
		close_pipe(fd);
		return ;
	}
	papi(node, fd);
	close_pipe(fd);
}
