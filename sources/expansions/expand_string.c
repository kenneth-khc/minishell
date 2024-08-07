/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 03:14:02 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:18:50 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/**
 * HACK: not sure what to do here to replicate the behaviour of $"" and $''
 * but it just takes the entire thing as a key and the contents within it
 * as a value to expand
 */
void	expand_string(t_Expansion_List *expansions, t_Token *token,
						char *dollar)
{
	char		*q_start;
	char		*q_end;
	t_String	*key;
	t_String	*value;
	t_Expansion	*new_expansion;

	q_start = &dollar[1];
	q_end = ft_strchr(q_start + 1, *q_start);
	key = string_extract(dollar, q_end);
	value = string_extract(q_start + 1, q_end - 1);
	if (value == NULL)
	{
		value = stringify("");
	}
	new_expansion = create_expansion(key, value, dollar - token->lex->start);
	add_expansion(expansions, new_expansion);
	update_token_lexeme(token, expansions, new_expansion);
}
