/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:11:05 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/11 19:47:40 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tree.h"
#include <stdlib.h>

#define ARR_SIZE 10

int	main(void)
{
	Tree	*tree;

	tree = calloc(1, sizeof(*tree));
	insert(tree, 10);
	insert(tree, 11);
	insert(tree, 12);
	insert(tree, 13);
	insert(tree, 14);
	insert(tree, 15);
	preorder(tree->root);
	printf("\n");
	inorder(tree->root);
	printf("\n");
	postorder(tree->root);
}


