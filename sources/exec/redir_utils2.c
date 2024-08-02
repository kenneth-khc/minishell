/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:28:41 by qang              #+#    #+#             */
/*   Updated: 2024/08/03 01:39:19 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "tree.h"
#include <stdbool.h>

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

