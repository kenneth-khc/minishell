/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:28:41 by qang              #+#    #+#             */
/*   Updated: 2024/08/04 00:36:53 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "tree.h"
#include <stdbool.h>
#include <unistd.h>

bool	special_cmd(t_Redir_Node *node)
{
	t_Exec_Node *node_left;

	if (node->left && node->left->type == EXEC_NODE)
	{
		node_left = (t_Exec_Node *)node->left;
		if (ft_strcmp2(node_left->command, "cd") == 0 || ft_strcmp2(node_left->command, "exit") == 0)
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
