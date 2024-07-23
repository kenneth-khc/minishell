/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:57:06 by qang              #+#    #+#             */
/*   Updated: 2024/07/23 18:04:13 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

char		**list_to_string(t_list *node, char *str);
void		unmatch(t_list **list, char *pattern);
static bool	match_pattern(char *pattern, char *str);

char	**list_to_string(t_list *node, char *str)
{
	int		i;
	char	**ret;
	t_list	*next;

	i = 0;
	if (ft_lstsize(node) == 0)
	{
		ret = mallocpromax(sizeof(char *) * 2);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	ret = mallocpromax(sizeof(char *) * (ft_lstsize(node) + 1));
	while (node)
	{
		next = node->next;
		ret[i] = node->content;
		free(node);
		i++;
		node = next;
	}
	ret[i] = NULL;
	return (ret);
}

static bool	match_pattern(char *pattern, char *str)
{
	if (!*pattern && !*str)
		return (true);
	else if (*pattern == '*')
	{
		if (!*(pattern + 1))
			return (true);
		while (*str)
		{
			if (match_pattern(pattern, str))
				return (true);
			str++;
		}
		return (match_pattern(pattern, str));
	}
	else
	{
		if (*pattern == *str)
			return (match_pattern(pattern + 1, str + 1));
		else
			return (false);
	}
}

void	unmatch(t_list **list, char *pattern)
{
	t_list	*prev;
	t_list	*node;
	t_list	*next;

	prev = NULL;
	next = NULL;
	node = *list;
	while (node)
	{
		if (!match_pattern(pattern, node->content))
		{
			next = node->next;
			if (prev == NULL)
				*list = node->next;
			else
				prev->next = node->next;
			ft_lstdelone(node, free);
			node = next;
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
}
