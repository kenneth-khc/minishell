/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:25:23 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/11 19:47:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdio.h>

/**
 * Print pre-order 
**/

void	preorder(TreeNode *node)
{
	if (node == NULL)
		return ;
	print_node(node);
	preorder(node->left_child);
	preorder(node->right_child);
}

void	postorder(TreeNode *node)
{
	if (node == NULL)
		return ;
	postorder(node->left_child);
	postorder(node->right_child);
	print_node(node);
}

void	inorder(TreeNode *node)
{
	if (node == NULL)
		return ;
	inorder(node->left_child);
	print_node(node);
	inorder(node->right_child);
}

void	print_node(TreeNode *node)
{
	printf("%d\n", node->num);
}
