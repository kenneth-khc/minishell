/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:36:18 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:53:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/**
 * Checks against the list of quotes to see if this is gonna expand
 * Expands in weak quotes " "
 * Do not expand in strong quotes ' '
 */
bool	is_expansion(char *c, t_Quote_List *quotes)
{
	int			i;
	t_Quotes	*pair;

	if (*c != '$' || c[1] == '\0')
		return (false);
	i = 0;
	while (i < quotes->pair_count)
	{
		pair = quotes->pairs[i];
		if (c > pair->start
			&& c < pair->end)
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

/**
 * Checks if a given character belongs within any of the expansions
 */
bool	in_expansions(t_Expansion_List *expansions, char *c)
{
	t_Expansion	*expansion;

	expansion = expansions->head;
	while (expansion)
	{
		if (expansion->start <= c
			&& c <= expansion->end)
		{
			return (true);
		}
		expansion = expansion->next;
	}
	return (false);
}
