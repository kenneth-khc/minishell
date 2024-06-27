/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:32:14 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 22:27:36 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

t_envar	*copy_env(t_envar *src);
void	del_var(char *key, t_entab *table);
t_envar	*get_var(char *key, t_entab *table);

t_envar	*get_var(char *key, t_entab *table)
{
	t_envar	*node;

	node = table->head;
	while (node)
	{
		if (ft_strcmp(key, node->key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	del_var(char *key, t_entab *table)
{
	t_envar	*node;

	node = table->head;
	while (node)
	{
		if (ft_strcmp(key, node->key) == 0)
		{
			if (node != table->head)
				node->prev->next = node->next;
			if (node != table->tail)
				node->next->prev = node->prev;
			if (node->val)
				free(node->val);
			free(node->key);
			free(node);
		}
		node = node->next;
	}
}

t_envar	*copy_env(t_envar *src)
{
	t_envar	*temp;

	temp = malloc(sizeof(t_envar));
	temp->key = ft_strdup(src->key);
	temp->val = ft_strdup(src->val);
	temp->display = src->display;
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}
