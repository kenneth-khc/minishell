/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:15:03 by qang              #+#    #+#             */
/*   Updated: 2024/07/13 00:49:18 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <fcntl.h>

void	exec_ast(t_Node *node);

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
		exit(0);
	}
	pid2 = forkpromax();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		exec_ast(node->right);
		exit(0);
	}
	close_pipe(fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	redir(t_Redir_Node *node)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		node->newfd = open(node->file, node->flags, node->mode);
		dup2(node->newfd, node->oldfd);
		close(node->newfd);
		exec_ast(node->left);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
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
	if (get_exit_status() == 0)
		return ;
	exec_ast(node->right);
}

void	exec_ast(t_Node *node)
{
	if (node->type == Exec_Node)
		exec((t_Exec_Node *)node);
	else if (node->type == Redir_Node)
		redir((t_Redir_Node *)node);
	else if (node->type == Pipe_Node)
		paip((t_Pipe_Node *)node);
	else if (node->type == AND_AND_NODE)
		andand(node);
	else if (node->type == OR_OR_NODE)
		oror(node);
}
