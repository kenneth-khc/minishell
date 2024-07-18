/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:49:01 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:53:41 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "execution.h"
#include "expansions.h"
#include "libft.h"
#include "tokens.h"
#include "quotes.h"
#include "definitions.h"

bool	parameter_expand(t_Token *token, t_entab *env)
{
	t_Chunk_List	chunks;
	char			*s;
	char			*e;
	bool			expanded;

	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	s = (char *)token->lexeme;
	e = s;
	expanded = false;
	while (s < (token->lexeme + ft_strlen(token->lexeme)))
	{
		if (*e == '\0' || (is_quote(*e) && quote_to_remove(&token->quotes, e)))
			chunkify_unexpanded_portion(&chunks, &s, &e);
		else if (*e == '$' && should_expand(e, &token->quotes))
		{
			expanded = chunkify_expansions(&chunks, env, &s, &e);
			s = e;
		}
		else
			e++;
	}
	free(token->lexeme);
	token->lexeme = join_chunks(&chunks);
	return (expanded);
}

bool	special_parameter(char *dollar)
{
	return (dollar[1] == '?'
		|| dollar[1] == '0'
		|| dollar[1] == '$');
}

void	expand_special_parameters(t_Chunk_List *chunks, char *dollar)
{
	char	*value;

	value = NULL;
	if (dollar)
	{
		if (dollar[1] == '?')
			value = ft_itoa(get_exit_status());
		else if (dollar[1] == '0')
			value = ft_strdup(SHELL);
		else if (dollar[1] == '$')
			value = ft_itoa(getpid());
		add_chunk(chunks, value);
	}
}

/**
 * A key is only a valid name if it starts with an underscore or alphabet.
 * Treat the $ as literal and do not expand if it is not
 * going to be a valid name.
 * For some reason, $"" $'' expands.
**/
bool	is_valid_key_start(char *dollar)
{
	return (dollar[1] == '_'
		//|| dollar[1] == '"'
		//|| dollar[1] == '\''
		|| ft_isalpha(dollar[1]));
}

/**
 * Check if the quote found is any of the original pair of unquoted quotes
 * in the input
 * If it is, skip over them as quote removal
 **/
bool	quote_to_remove(t_Quote_List *quote_list, char *quote)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (quote == pair->start || quote == pair->end)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * Check if the dollar found belongs between any of the pair of quotes
 * in the word
 * If found between strong quotes (''), do not expand
**/
bool	should_expand(char *dollar, t_Quote_List *quote_list)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (dollar > pair->start
			&& dollar < pair->end)
		{
			if (pair->quote == STRONG)
				return (false);
			else if (pair->quote == WEAK)
				return (true);
		}
		i++;
	}
	return (true);
}
