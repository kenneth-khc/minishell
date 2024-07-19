/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:57:06 by qang              #+#    #+#             */
/*   Updated: 2024/07/19 19:59:37 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

bool  match_pattern(char *pattern, char *str);
char  **list_to_string(t_list *node, char *str);
void	unmatch(t_list **list, char *pattern);

char  **list_to_string(t_list *node, char *str)
{
	int i;
	char  **ret;
	t_list *next;

	i = 0;
	if (ft_lstsize(node) == 0)
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	ret = malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	if (ret)
	{
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
	return (NULL);
}

void unmatch(t_list **list, char *pattern)
{
	t_list  *prev = NULL;
	t_list  *node = *list;
	t_list  *next;

	next = NULL;
	while (node)
	{
		if (!match_pattern(pattern, node->content))
		{
			next = node->next;
			if (prev == NULL)
				*list = node->next;
			else
				prev->next = node->next;
			free(node->content);
			free(node);
			node = NULL;
			node = next;
		} 
		else
		{
			prev = node;
			node = node->next;
		}	
	}
}

bool  match_pattern(char *pattern, char *str)
{
	int pat_i;
	int str_i;

	pat_i = 0;
	str_i = 0;
	while (pattern[pat_i] && str[str_i])
	{
		if (pattern[pat_i] == '*')
		{
			while (pattern[pat_i + 1] == '*')
				pat_i++;
			if (pattern[pat_i + 1] == '\0')
				return (true);
			while (str[str_i] && pattern[pat_i + 1] != str[str_i])
				str_i++;
			if (pattern[pat_i + 1] == str[str_i])
				pat_i++;
			else
				return (false);
		}
		if (pattern[pat_i] == str[str_i])
		{
			pat_i++;
			str_i++;
		}
		else
			return (false);
	}
	return (pattern[pat_i] == '\0' && str[str_i] == '\0');
}