/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:24:13 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 22:46:00 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

t_entab		*init_env_table(char **env);
t_envar		*new_env_var(const char *str);
void		free_env(t_entab *table);
void		add_var(char *str, t_entab *table);
static void	update_var(t_envar *node, t_envar *new);

static void	update_var(t_envar *node, t_envar *new)
{
	if (ft_strcmp(new->key, "PWD") == 0)
	{
		if (node->pwd)
		{
			free(node->pwd);
			node->pwd = new->val;
		}
		else
			node->pwd = new->val;
	}
	else
	{
		if (new->val)
		{
			if (node->val)
				free(node->val);
			node->val = new->val;
		}
		node->state = new->state;
	}
	free(new->key);
	free(new);
}

void	add_var(char *str, t_entab *table)
{
	t_envar	*new;

	new = new_env_var(str);
	if (table->head == NULL)
	{
		table->head = new;
		return ;
	}
	if (get_var(new->key, table) == NULL)
	{
		table->tail->next = new;
		new->prev = table->tail;
		table->tail = new;
		return ;
	}
	else
		update_var(get_var(new->key, table), new);
}

t_envar	*new_env_var(const char *str)
{
	char	*temp;
	char	*key;
	char	*val;
	t_envar	*new;

	new = mallocpromax(sizeof(t_envar));
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
	new->pwd = NULL;
	new->prev = NULL;
	new->next = NULL;
	new->state = DISPLAY;
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
		if (temp->pwd)
			free(temp->pwd);
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
	table = mallocpromax(sizeof(t_entab));
	prev = NULL;
	temp = NULL;
	while (env[++i])
	{
		temp = new_env_var(env[i]);
		temp->state |= EXPORT;
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
