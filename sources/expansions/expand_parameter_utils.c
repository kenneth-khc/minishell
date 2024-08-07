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
#include "definitions.h"

/**
* These are the only special shell parameters implemented
* $? gives the last exit status
* $0 gives the name of the shell
* $$ gives the current process ID
**/
bool	special_parameter(char *dollar)
{
	return (dollar[1] == '?'
		|| dollar[1] == '0'
		|| dollar[1] == '$');
}

/**
 * Check if it is a quoted string next to the dollar sign
 * If it is, we skip over the dollar and continue as usual because we do not
 * implement the "ANSI-C Quoting" and "Locale-Specific Translation" features
 **/
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

bool	strong_quoted(char *c, t_Quote_List *quotes)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quotes->pair_count)
	{
		pair = quotes->pairs[i];
		if (c > pair->start
			&& c < pair->end)
		{
			if (pair->quote == STRONG)
				return (true);
			else if (pair->quote == WEAK)
				return (false);
		}
		i++;
	}
	return (false);
}

/**
 * Checks against the list of quotes to see if this is gonna expand
 * Expands in weak quotes " "
 * Do not expand in strong quotes ' '
 */
bool	is_expansion(char *c, t_Quote_List *quotes)
{
	if (c == NULL)
		return (false);
	if (*c != '$')
		return (false);
	if (dollar_prefix_string(c, quotes))
		return (true);
	else if (special_parameter(c) && !strong_quoted(c, quotes))
		return (true);
	else if (is_identifier_start(c) && !strong_quoted(c, quotes))
		return (true);
	else
		return (false);
}

/**
 * Checks if a given character belongs within any of the expansions
 */
bool	in_expansions(t_Expansion_List *expansions, char *c)
{
	t_Expansion	*expansion;

	if (expansions == NULL)
		return (false);
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
