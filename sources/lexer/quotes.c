/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:16:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/15 22:07:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "tokens.h"
#include <stdio.h>
#include "libft.h"

t_Quote_List	find_quotes(t_Token *token)
{
	struct s_Quote_List	list;
	char			*word = (char*)token->lexeme;
	t_Quotes		*quotes;

	list = (struct s_Quote_List){0, NULL};
	quotes = find_next_pair(word, &word);
	while (quotes != NULL
		&& word <= token->lexeme + ft_strlen(token->lexeme))
	{
		store_quotes(&list, quotes);
		quotes = find_next_pair(word, &word);
	}
	return (list);
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

t_Quotes	*find_next_pair(char *word, char **next_start)
{
	t_Quotes	*quotes;(void)quotes;
	char		*s;

	s = ft_strpbrk(word, is_quote);
	if (s == NULL)
		return (NULL);
	quotes = ft_calloc(1, sizeof(*quotes));
	quotes->quote = *s;
	quotes->start = s;
	s++;
	while (*s != quotes->quote)
	{
		s++;
	}
	quotes->end = s;
	*next_start = quotes->end + 1;
	return (quotes);
}

void	store_quotes(t_Quote_List *list, t_Quotes *quotes)
{
	t_Quotes	**new;
	int			i;

	list->pair_count++;
	new = ft_calloc(list->pair_count + 1, sizeof(t_Quotes *));
	i = 0;
	while (i < list->pair_count - 1)
	{
		new[i] = list->quotes[i];
		i++;
	}
	new[i] = quotes;
	list->quotes = new;
}


void	print_quote_list(t_Token *token)
{
	printf("Start: %p End: %p\n", token->lexeme, token->lexeme + ft_strlen(token->lexeme) - 1);
	
	int	i = 0;
	t_Quotes	*q;

	printf("Quotes: \n");
	while (i < token->quotes.pair_count)
	{
		q = token->quotes.quotes[i];
		printf("Start: %p End: %p\n", q->start, q->end);
		i++;
	}
	printf("\n");
}

