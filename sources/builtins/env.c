/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:18:39 by qang              #+#    #+#             */
/*   Updated: 2024/07/10 18:26:15 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

static void print_val(t_envar *node)
{
  if (!node->fakepwd)
    printf("%s=%s\n", node->key, node->val);
  else
    printf("%s=%s\n", node->key, node->pwd);
}

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
		if (node->val != NULL && node->display)
      print_val(node);
		node = node->next;
	}
	if (absfn)
		printf("%s=%s\n", absfn->key, absfn->val);
	return (0);
}
