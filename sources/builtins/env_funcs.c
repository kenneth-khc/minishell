/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:24:13 by qang              #+#    #+#             */
/*   Updated: 2024/07/06 00:59:03 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

t_envar	*new_env_var(const char *str);
void	add_var(char *str, t_entab *table);
void	free_env(t_entab *table);
t_entab	*init_env_table(char **env);

static void	update_var(t_envar *node, t_envar *new)
{
	char	*temp;

	temp = node->val;
	if (new->val)
	{
		node->val = new->val;
		if (temp)
			free(temp);
	}
	node->display = new->display;
	free(new->key);
	free(new);
}

void	add_var(char *str, t_entab *table)
{
	t_envar	*node;
	t_envar	*new;

	node = table->head;
	new = new_env_var(str);
	if (table->head == NULL)
	{
		table->head = new;
		return ;
	}
	while (node)
	{
		if (ft_strcmp(new->key, node->key) == 0)
		{
			update_var(node, new);
			return ;
		}
		node = node->next;
	}
	node = table->tail;
	node->next = new;
	new->prev = node;
	table->tail = new;
}

t_envar	*new_env_var(const char *str)
{
	char	*temp;
	char	*key;
	char	*val;
	t_envar	*new;

	new = malloc(sizeof(t_envar));
	temp = ft_strchr(str, '=');
	key = ft_substr(str, 0, temp - str);
	if (temp == NULL)
		val = NULL;
	else if (temp + 1 == NULL)
		val = ft_strdup("");
	else
		val = ft_strdup(temp + 1);
	new->key = key;
	new->val = val;
	new->prev = NULL;
	new->next = NULL;
	new->display = true;
	return (new);
}

void	free_env(t_entab *table)
{
	t_envar	*node;
	t_envar	*temp;

	node = table->head;
	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->key);
		if (temp->val)
			free(temp->val);
		free(temp);
	}
	free(table);
}

t_entab	*init_env_table(char **env)
{
	int		i;
	t_envar	*prev;
	t_envar	*temp;
	t_entab	*table;

	i = -1;
	table = malloc(sizeof(t_entab));
	prev = NULL;
	temp = NULL;
	while (env[++i])
	{
		temp = new_env_var(env[i]);
		if (prev == NULL)
			table->head = temp;
		else
		{
			prev->next = temp;
			temp->prev = prev;
		}
		prev = temp;
	}
	table->tail = temp;
	return (table);
}
