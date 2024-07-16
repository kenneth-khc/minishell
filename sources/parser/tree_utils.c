/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:02:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/05 20:01:51 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "libft.h"
#include <stdlib.h>

t_Node	*create_node(enum e_Node_Type type)
{
	t_Node	*node;

	node = ft_calloc(1, sizeof(*node));
	node->type = type;
	return (node);
}

t_Exec_Node	*create_exec_node(const char *cmd_name, t_entab *envtab)
{
	t_Exec_Node	*node;

	node = ft_calloc(1, sizeof(*node));
	node->type = Exec_Node;
	node->left = NULL;
	node->command = cmd_name;
	node->table = envtab;
	return (node);
}

t_Redir_Node	*create_redir_node(int oldfd, const char *filename,
int flags, mode_t mode)
{
	t_Redir_Node	*node;
	
	node = ft_calloc(1, sizeof(*node));
	node->type = Redir_Node;
	node->left = NULL;
	node->oldfd = oldfd;
	node->file = (char *)filename;
	node->flags = flags;
	node->mode = mode;

	return (node);
}

void	add_exec_arguments(t_Exec_Node *exec_node, const char *arg)
{
	int	i;
	int			old_count;
	const char	**temp;

	i = 0;
	if (arg == NULL || *arg == '\0')
		return ;
	old_count = exec_node->arg_count;
	if (exec_node->arg_count == 0)
		exec_node->command = arg;
	exec_node->arg_count++;
	temp = ft_calloc(exec_node->arg_count + 1, sizeof(const char *));
	while (i < old_count)
	{
		temp[i] = exec_node->args[i];
		i++;
	}
	free(exec_node->args);
	temp[i] = arg;
	exec_node->args = temp;
}

t_Node	*get_tail(t_Node *node)
{
	while (node->left != NULL)
		node = node->left;
	return (node);
}

