/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:15:03 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 22:54:36 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void	exec_ast(t_Node *node);
void	oror(t_Node *node);
void	andand(t_Node *node);
void	paip(t_Pipe_Node *node);
void	subshell(t_Node *node);

void	subshell(t_Node *node)
{
	int	pid;
	int	status;

	pid = forkpromax();
	if (pid == 0)
	{
		exec_ast(node->left);
		exit(get_exit_status());
	}
	else
	{
		waitpid(pid, &status, 0);
		set_exit_status(WEXITSTATUS(status));
	}
}

void	paip(t_Pipe_Node *node)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pipepromax(fd);
	pid1 = forkpromax();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		exec_ast(node->left);
		exit(get_exit_status());
	}
	pid2 = forkpromax();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		exec_ast(node->right);
		exit(get_exit_status());
	}
	close_pipe(fd);
	set_exit_status(wait_for_child(pid1));
	set_exit_status(wait_for_child(pid2));
}

void	andand(t_Node *node)
{
	exec_ast(node->left);
	if (get_exit_status() != 0)
		return ;
	else
		exec_ast(node->right);
}

void	oror(t_Node *node)
{
	exec_ast(node->left);
	if (get_exit_status() == 0 || get_exit_status() == 130)
		return ;
	exec_ast(node->right);
}

void	exec_ast(t_Node *node)
{
	if (node == NULL)
		return ;
	if (node->type == Exec_Node)
		exec((t_Exec_Node *)node);
	else if (node->type == Redir_Node)
		redir((t_Redir_Node *)node);
	else if (node->type == ASS_NODE)
		ass_var((t_Ass_Node *)node);
	else if (node->type == SUBSHELL_NODE)
		subshell(node);
	else if (node->type == Pipe_Node)
		paip((t_Pipe_Node *)node);
	else if (node->type == AND_AND_NODE)
		andand(node);
	else if (node->type == OR_OR_NODE)
		oror(node);
}
