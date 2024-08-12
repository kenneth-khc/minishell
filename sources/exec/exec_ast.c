/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:15:03 by qang              #+#    #+#             */
/*   Updated: 2024/08/12 16:45:43 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include <sys/wait.h>
#include <unistd.h>

void	exec_ast(t_Node *node);
void	oror(t_Node *node);
void	andand(t_Node *node);
void	subshell(t_Node *node);

void	subshell(t_Node *node)
{
	int	pid;

	pid = forkpromax();
	if (pid == 0)
	{
		exec_ast(node->left);
		exit(get_exit_status());
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid));
	}
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
	if (node->type == EXEC_NODE)
		exec((t_Exec_Node *)node);
	else if (node->type == REDIR_NODE)
		redir((t_Redir_Node *)node);
	else if (node->type == ASS_NODE)
		ass_var((t_Ass_Node *)node);
	else if (node->type == SUBSHELL_NODE)
		subshell(node);
	else if (node->type == PIPE_NODE)
		paip((t_Pipe_Node *)node);
	else if (node->type == AND_AND_NODE)
		andand(node);
	else if (node->type == OR_OR_NODE)
		oror(node);
}
