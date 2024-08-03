/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:28:41 by qang              #+#    #+#             */
/*   Updated: 2024/08/03 17:01:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "tree.h"
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

bool	special_cmd(t_Redir_Node *node);
void	redir_special_cmd(t_Redir_Node *node);
void	run_heredoc(t_Redir_Node *node, char *next_heredoc);
void	run_redir(t_Redir_Node *node);
void	write_heredoc(t_Redir_Node *node, char *next_heredoc);

bool	special_cmd(t_Redir_Node *node)
{
	t_Exec_Node	*node_left;

	if (node->left && node->left->type == EXEC_NODE)
	{
		node_left = (t_Exec_Node *)node->left;
		if (ft_strcmp2(node_left->command, "cd") == 0
			|| ft_strcmp2(node_left->command, "exit") == 0)
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

void	write_heredoc(t_Redir_Node *node, char *next_heredoc)
{
	int	pid1;
	int	fd;

	pid1 = forkpromax();
	if (pid1 == 0)
	{
		set_sig();
		fd = openpromax(next_heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		write_heredoc_loop(node, fd);
		close(fd);
		exit(0);
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid1));
	}
}

void	run_heredoc(t_Redir_Node *node, char *next_heredoc)
{
	int	pid1;
	int	fd;

	pid1 = forkpromax();
	if (pid1 == 0)
	{
		fd = openpromax(next_heredoc, O_RDONLY, 0644);
		unlink(next_heredoc);
		init_signal();
		if (node->last_heredoc)
			dup2(fd, node->oldfd);
		close(fd);
		exec_ast(node->left);
		exit(0);
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid1));
	}
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
		exit(0);
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid1));
	}
}
