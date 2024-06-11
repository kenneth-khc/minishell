/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:28:10 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/11 19:28:16 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdlib.h>

TreeNode	*create_node(int data)
{
	TreeNode	*node;

	node = calloc(1, sizeof(*node));
	node->num = data;
	node->left_child = NULL;
	node->right_child = NULL;
	node->parent = NULL; // how do I assign parent??
	return (node);
}

void	insert(Tree *tree, int data)
{
	insert_node(&tree->root, data);
}

void	insert_node(TreeNode **node, int data)
{
	TreeNode	*n = *node;

	if (*node == NULL)
	{
		*node = create_node(data);
		return ;
	}
	else if (n->left_child && n->right_child)
	{
		insert_node(&n->left_child, data);
	}
	else if (n->left_child == NULL)
	{
		n->left_child = create_node(data);
		return ;
	}
	else if (n->right_child == NULL)
	{
		n->right_child = create_node(data);
		return ;
	}
}
