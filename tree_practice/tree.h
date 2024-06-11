/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:26:14 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/11 19:26:26 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct TreeNode
{
	int				num;
	struct TreeNode	*parent;
	struct TreeNode	*left_child;
	struct TreeNode	*right_child;
}	TreeNode;

typedef struct Tree
{
	struct TreeNode	*root;
}	Tree;


// Tree	*init_tree(char *str);

void	insert(Tree *tree, int data);
void	insert_node(TreeNode **node, int data);

void	preorder(TreeNode *node);
void	postorder(TreeNode *node);
void	inorder(TreeNode *node);
void	print_node(TreeNode *node);
