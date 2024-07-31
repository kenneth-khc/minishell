/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:16:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 09:29:56 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "quotes.h"
#include "tokens.h"
#include "libft.h"

t_Quote_List	find_quotes(t_Token *token)
{
	struct s_Quote_List	list;
	struct s_Quotes		*quotes;
	char				*word;

	word = token->lexeme;
	list = (struct s_Quote_List){0, NULL};
	quotes = find_next_pair(word, &word);
	while (quotes != NULL
		&& word <= word + ft_strlen(word))
	{
		store_quotes(&list, quotes);
		quotes = find_next_pair(word, &word);
	}
	return (list);
}

t_Quotes	*find_next_pair(char *word, char **next_start)
{
	t_Quotes	*quotes;
	char		*s;

	s = ft_strpbrk(word, is_quote);
	if (s == NULL)
		return (NULL);
	quotes = callocpromax(1, sizeof(*quotes));
	quotes->quote = *s;
	quotes->start = s;
	s++;
	while (*s != quotes->quote)
	{
		s++;
	}
	quotes->end = s;
	if (next_start)
		*next_start = quotes->end + 1;
	return (quotes);
}

void	store_quotes(t_Quote_List *list, t_Quotes *quotes)
{
	t_Quotes	**new;
	int			i;

	list->pair_count++;
	new = callocpromax(list->pair_count, sizeof(t_Quotes *));
	i = 0;
	while (i < list->pair_count - 1)
	{
		new[i] = list->pairs[i];
		i++;
	}
	new[i] = quotes;
	list->pairs = new;
}

/**
 * Check if the quote found is any of the original pair of unquoted quotes
 * in the input
 * If it is, skip over them as quote removal
 **/
bool	quote_to_remove(t_Quote_List *quote_list, char *c)
{
	int			i;
	t_Quotes	*pair;

	if (!is_quote(*c))
		return (false);
	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (c == pair->start || c == pair->end)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	free_quote_list(t_Quote_List *list)
{
	int	i;

	i = 0;
	while (i < list->pair_count)
	{
		free(list->pairs[i]);
		i++;
	}
	free(list->pairs);
}
