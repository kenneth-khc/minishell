/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:49:01 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 16:21:55 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expansions.h"
#include "quotes.h"

static bool	dollar_prefix_string(char *dollar, t_Quote_List *quote_list);

bool	try_variable_expansion(t_Chunk_List *chunks, t_Quote_List *quote_pairs,
			t_entab *env, t_Range *p)
{
	bool	token_expanded;

	token_expanded = false;
	if (dollar_prefix_string(p->end, quote_pairs))
		point_to_new_chunk(p);
	else if (variable_should_expand(p->end, quote_pairs))
	{
		token_expanded = do_variable_expansion(chunks, env, p);
		p->start = p->end;
	}
	else
	{
		p->end++;
	}
	return (token_expanded);
}

/**
 * Check if it is a quoted string next to the dollar sign
 * If it is, we skip over the dollar and continue as usual because we do not
 * implement the "ANSI-C Quoting" and "Locale-Specific Translation" features
 **/
static bool	dollar_prefix_string(char *dollar, t_Quote_List *quote_list)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (dollar + 1 == pair->start
			&& pair->end > pair->start)
			return (true);
		i++;
	}
	return (false);
}

/**
 * Check if the dollar found belongs between any of the pair of quotes
 * in the word
 * If found between strong quotes (''), do not expand
**/
bool	variable_should_expand(char *dollar, t_Quote_List *quote_list)
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
