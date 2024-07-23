/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:12:55 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 10:13:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "expansions.h"
#include "quotes.h"

bool	check_expansions(t_Range *p, t_Quote_List *quote_pairs, t_entab *env,
			t_Chunk_List *chunks)
{
	bool	expanded;

	expanded = false;
	if (dollar_prefix_string(p->end, quote_pairs))
		p->end += 1;
	else if (should_expand(p->end, quote_pairs))
	{
		expanded = chunkify_expansions(chunks, env, p);
		p->start = p->end;
	}
	return (expanded);
}

bool	dollar_prefix_string(char *dollar, t_Quote_List *quote_list)
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
