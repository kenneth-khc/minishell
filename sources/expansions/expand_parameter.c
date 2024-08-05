/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:47:00 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:29:04 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "definitions.h"
#include "ft_string.h"

static bool
dollar_prefix_string(char *dollar, t_Quote_List *quote_list);

static bool
special_parameter(char *dollar);

void	parameter_expansion(t_Expansion_List *expansions, t_Token *token,
							t_entab *env)
{
	char	*c;

	c = token->lex->start;
	while (*c)
	{
		if (is_expansion(c, &token->quotes))
		{
			if (dollar_prefix_string(c, &token->quotes))
				expand_string(expansions, token, c);
			else if (special_parameter(c))
				expand_special_parameter(expansions, token, c);
			else if (is_identifier_start(c))
				expand_variable(expansions, token, c, env);
			if (expansions->tail && expansions->tail->end)
				c = expansions->tail->end + 1;
			else
				c++;
		}
		else
			c++;
	}
}

/**
* These are the only special shell parameters implemented
* $? gives the last exit status
* $0 gives the name of the shell
* $$ gives the current process ID
**/
static bool	special_parameter(char *dollar)
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
