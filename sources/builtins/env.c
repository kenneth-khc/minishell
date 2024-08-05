/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:18:39 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 22:02:48 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include <stdio.h>

int			print_env(char **args, t_entab *table);
static void	print_val(t_envar *node);

int	dont_print_env(char **args)
{
	ft_dprintf(2, "%s: env: %s: No such file or directory\n",
		SHELL, args[1]);
	return (127);
}

static void	print_val(t_envar *node)
{
	if (node->pwd)
		printf("%s=%s\n", node->key, node->pwd);
	else
		printf("%s=%s\n", node->key, node->val);
}

int	print_env(char **args, t_entab *table)
{
	t_envar	*node;
	t_envar	*absfn;

	absfn = NULL;
	node = table->head;
	if (length(args) > 1)
		return (dont_print_env(args));
	while (node)
	{
		if (ft_strcmp(node->key, "_") == 0)
		{
			absfn = node;
			node = node->next;
			continue ;
		}
		if (node->val != NULL
			&& ((node->state & DISPLAY) && !(node->state & LOCAL)))
			print_val(node);
		node = node->next;
	}
	if (absfn)
		printf("%s=%s\n", absfn->key, absfn->val);
	return (0);
}
