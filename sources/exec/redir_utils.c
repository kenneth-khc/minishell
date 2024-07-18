/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:07:13 by qang              #+#    #+#             */
/*   Updated: 2024/07/18 10:27:35 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char		*expand_line(char *line, t_entab *table);
static char	*join_list(t_list *head);
static char	*get_node_val(char *key, t_entab *table);
static char	*get_type(char *str, t_entab *table);
static int	skip_next(char *str);

static int	skip_next(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1])
	{
		if (!ft_isalpha(str[i + 1]))
			return (2);
		else
		{
			while (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			return (i + 1);
		}
	}
	return (i + 1);
}

static char	*get_node_val(char *key, t_entab *table)
{
	t_envar	*node;

	node = get_var(key, table);
	if (!(node->state | (LOCAL | EXPORT)))
		return (ft_strdup(""));
	else if (node->pwd)
		return (ft_strdup(node->pwd));
	else
		return (ft_strdup(node->val));
}

static char	*get_type(char *str, t_entab *table)
{
	char	*temp1;

	if (*(str + 1))
	{
		if (*(str + 1) == '?')
			return (ft_itoa(get_exit_status()));
		else if (*(str + 1) == ' ')
			return (ft_strdup("$ "));
		else if (!ft_isalpha(*(str + 1)))
			return (ft_strdup(""));
		else
		{
			temp1 = str;
			while (ft_isalnum(*(temp1 + 1)) || *(temp1 + 1) == '_')
				temp1++;
			temp1 = ft_substr(str, 1, temp1 - str);
			if (get_var(temp1, table) == NULL)
				return (ft_strdup(""));
			else
				return (get_node_val(temp1, table));
		}
	}
	return (ft_strdup(""));
}

static char	*join_list(t_list *head)
{
	t_list	*temp;
	t_list	*next;
	char	*ret;
	char	*str;

	ret = "";
	temp = head;
	while (temp)
	{
		str = (char *)temp->content;
		ret = ft_strjoin(ret, str);
		next = temp->next;
		ft_lstdelone(temp, free);
		temp = next;
	}
	return (ret);
}

char	*expand_line(char *line, t_entab *table)
{
	int		prev;
	int		curr;
	char	*val;
	t_list	*head;

	prev = 0;
	curr = 0;
	head = NULL;
	while (line[curr])
	{
		if (line[curr] == '$')
		{
			ft_lstadd_back(&head,
				ft_lstnew(ft_substr(line, prev, curr - prev)));
			val = get_type(line + curr, table);
			ft_lstadd_back(&head, ft_lstnew(val));
			curr += skip_next(line + curr);
			prev = curr;
		}
		else
			curr++;
	}
	ft_lstadd_back(&head, ft_lstnew(ft_substr(line, prev, curr - prev)));
	return (join_list(head));
}
