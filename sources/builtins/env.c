/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:18:39 by qang              #+#    #+#             */
/*   Updated: 2024/07/05 18:51:03 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

int	print_env(char **args, t_entab *table)
{
	t_envar	*node;
	t_envar	*absfn;

	node = table->head;
	if (length(args) > 1)
		printf("%s: env: %s: No such file or directory\n", SHELL, args[1]);
	while (node)
	{
		if (ft_strcmp(node->key, "_") == 0)
		{
			absfn = node;
			node = node->next;
			continue ;
		}
		if (node->val != NULL && node->display == true)
			printf("%s=%s\n", node->key, node->val);
		node = node->next;
	}
	if (absfn)
		printf("%s=%s\n", absfn->key, absfn->val);
	return (0);
}
