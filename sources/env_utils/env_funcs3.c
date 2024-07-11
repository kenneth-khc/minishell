/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:11:02 by qang              #+#    #+#             */
/*   Updated: 2024/07/11 23:17:06 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

char	**env_convert(t_entab *table);
void	incr_shlvl(t_entab *table);
void  special_pwd(t_envar *node, t_envar *new);

static char	**convert(char **ret, t_envar *node, int size)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < size)
	{
		if (((node->state & EXPORT) || ft_strcmp(node->key, "PWD") == 0)
      && node->val)
		{
        temp = ft_strjoin(node->key, "=");
        ret[i] = ft_strjoin(temp, node->val);
        free(temp);
        i++;
    }
		node = node->next;
	}
	return (ret);
}

char	**env_convert(t_entab *table)
{
	t_envar	*node;
	int		i;
	char	**ret;

	node = table->head;
	i = 0;
	while (node)
	{
		if (((node->state & EXPORT) || ft_strcmp(node->key, "PWD") == 0)
      && node->val)
			i++;
		node = node->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	convert(ret, table->head, i);
	ret[i] = 0;
	return (ret);
}

void	incr_shlvl(t_entab *table)
{
	t_envar	*shlvl;
	int		lvl;

	shlvl = get_var("SHLVL", table);
	if (shlvl)
	{
		lvl = ft_atoi(shlvl->val);
		lvl++;
		free(shlvl->val);
		shlvl->val = ft_itoa(lvl);
	}
}

void  add_ass(char *str, t_entab *table)
{
	t_envar	*new;

	new = new_env_var(str);
	if (get_var(new->val, table))
		add_var(str, table);
	else
	{
		add_var(str, table);
		new->state = LOCAL;
	}
	free(new->key);
	if (new->val)
		free(new->val);
	free(new);
}

void  special_pwd(t_envar *node, t_envar *new)
{
	if (node->state & LOCAL)
		free(node->pwd);
	node->state |= LOCAL;
	node->pwd = new->val;
	free(new->key);
	free(new);
}
