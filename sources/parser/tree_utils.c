/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:02:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 18:17:19 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "libft.h"
#include <stdlib.h>

/**
 * Create a general node of type type
**/
t_Node	*node(enum e_Node_Type type)
{
	t_Node	*node;

	node = callocpromax(1, sizeof(*node));
	node->type = type;
	return (node);
}

/**
 * Create an execution node with the command name passed in and a pointer
 * to the environment
**/
t_Exec_Node	*exec_node(const char *cmd, t_entab *env)
{
	t_Exec_Node	*cmd_node;

	cmd_node = callocpromax(1, sizeof(*cmd_node));
	cmd_node->type = EXEC_NODE;
	cmd_node->command = cmd;
	cmd_node->table = env;
	return (cmd_node);
}

/**
 * Store the arguments for the command in an array to be passed in to
 * execve()
**/
void	add_exec_arguments(t_Exec_Node *exec_node, const char *arg)
{
	int			i;
	int			old_count;
	const char	**temp;

	i = 0;
	if (arg == NULL)
		return ;
	old_count = exec_node->arg_count;
	if (exec_node->arg_count == 0)
		exec_node->command = arg;
	exec_node->arg_count++;
	temp = callocpromax(exec_node->arg_count + 1, sizeof(const char *));
	while (i < old_count)
	{
		temp[i] = exec_node->args[i];
		i++;
	}
	free(exec_node->args);
	temp[i] = arg;
	exec_node->args = temp;
}

/**
 * Get the tail of the tree, traversing through all the left children
**/
t_Node	*get_tail(t_Node *node)
{
	if (node)
	{
		while (node->left != NULL)
			node = node->left;
		return (node);
	}
	return (NULL);
}

/**
 * Free the tree after done walking through it
 * For execution nodes, the pointer holding the arguments also have to be freed
**/
void	free_tree(t_Node *node)
{
	t_Node			*temp;
	t_Exec_Node		*enode;
	t_Redir_Node	*rnode;

	temp = node;
	if (node == NULL)
		return ;
	if (node->type == EXEC_NODE)
	{
		enode = (t_Exec_Node *)node;
		free(enode->args);
	}
	else if (node->type == REDIR_NODE)
	{
		rnode = (t_Redir_Node *)node;
		if (rnode->heredoc)
			free(rnode->delim);
	}
	free_tree(node->left);
	free_tree(node->right);
	free(temp);
}
