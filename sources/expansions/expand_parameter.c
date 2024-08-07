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

static char
*find_next_dollar(t_Token *token);

void	parameter_expansion(t_Expansion_List *expansions, t_Token *token,
							t_entab *env)
{
	char	*c;

	c = find_next_dollar(token);
	while (c && c < token->lex->end)
	{
		if (is_expansion(c, &token->quotes)
			&& !in_expansions(expansions, c))
		{
			if (dollar_prefix_string(c, &token->quotes))
				expand_string(expansions, token, c);
			else if (special_parameter(c))
				expand_special_parameter(expansions, token, c);
			else if (is_identifier_start(c))
				expand_variable(expansions, token, c, env);
			c = find_next_dollar(token);
		}
		else
			c++;
	}
}

static char	*find_next_dollar(t_Token *token)
{
	char	*c;

	c = token->lex->start;
	while (c < token->lex->end)
	{
		if (is_expansion(c, &token->quotes))
			return (c);
		c++;
	}
	return (NULL);
}
