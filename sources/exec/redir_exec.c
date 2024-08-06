/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 20:23:00 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include <fcntl.h>
#include <unistd.h>

void			redir(t_Redir_Node *node);
void			run_redir(t_Redir_Node *node);
static bool		special_cmd(t_Redir_Node *node);
static void		redir_special_cmd(t_Redir_Node *node);
static void		redir_delim(t_Redir_Node *node);

static void	redir_delim(t_Redir_Node *node)
{
	char	*next_heredoc;

	next_heredoc = get_next_heredoc();
	write_heredoc(node, next_heredoc);
	if (get_exit_status() == 130)
		return ;
	if (special_cmd(node))
	{
		node->file = next_heredoc;
		redir_special_cmd(node);
		free(next_heredoc);
		return ;
	}
	run_heredoc(node, next_heredoc);
	free(next_heredoc);
}

bool	special_cmd(t_Redir_Node *node)
{
	t_Exec_Node	*node_left;
	t_Node		*temp;

	if (!node)
		return (false);
	if (node->left && node->left->type == EXEC_NODE)
	{
		node_left = (t_Exec_Node *)node->left;
		if (ft_strcmp2(node_left->command, "cd") == 0
			|| ft_strcmp2(node_left->command, "exit") == 0)
			return (true);
		return (false);
	}
	else if (node->left && node->left->type == REDIR_NODE)
	{
		temp = (t_Node *)node;
		while (temp->left->type == REDIR_NODE)
			temp = temp->left;
		if (special_cmd((t_Redir_Node *)temp))
			return (true);
		return (false);
	}
	return (false);
}

void	redir_special_cmd(t_Redir_Node *node)
{
	int	temp_fd[2];
	int	fd;

	temp_fd[0] = dup(STDIN_FILENO);
	temp_fd[1] = dup(STDOUT_FILENO);
	check_permissions((char *)node->file, node->direction);
	fd = openpromax((char *)node->file, node->flags, node->mode);
	dup2(fd, node->oldfd);
	close(fd);
	exec_ast(node->left);
	dup2(temp_fd[0], STDIN_FILENO);
	dup2(temp_fd[1], STDOUT_FILENO);
	close_pipe(temp_fd);
}

void	run_redir(t_Redir_Node *node)
{
	int	pid1;
	int	fd;

	pid1 = forkpromax();
	if (pid1 == 0)
	{
		check_permissions((char *)node->file, node->direction);
		fd = openpromax((char *)node->file, node->flags, node->mode);
		dup2(fd, node->oldfd);
		close(fd);
		exec_ast(node->left);
		exit(get_exit_status());
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid1));
	}
}

void	redir(t_Redir_Node *node)
{
	if (node->heredoc)
	{
		redir_delim(node);
		return ;
	}
	if (special_cmd(node))
	{
		redir_special_cmd(node);
		return ;
	}
	run_redir(node);
}
