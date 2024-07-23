/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:57:06 by qang              #+#    #+#             */
/*   Updated: 2024/07/23 16:20:10 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

char		**list_to_string(t_list *node, char *str);
void		unmatch(t_list **list, char *pattern);
// static bool	match_pattern(char *pattern, char *str, int pat_i, int str_i);

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
	int pat_i = 0;
	int str_i = 0;
	int star_idx = -1;
	int match_idx = 0;

	while (str[str_i])
	{
		if (pattern[pat_i] == '*')
		{
			star_idx = pat_i;
			match_idx = str_i;
			pat_i++;
		}
		else if (pattern[pat_i] == str[str_i])
		{
			pat_i++;
			str_i++;
		}
		else if (star_idx != -1)
		{
			pat_i = star_idx + 1;
			match_idx++;
			str_i = match_idx;
		}
		else
			return false;
	}
	while (pattern[pat_i] == '*')
			pat_i++;
	return pattern[pat_i] == '\0';
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
