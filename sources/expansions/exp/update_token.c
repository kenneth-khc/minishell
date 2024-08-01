/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:28:50 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/05 09:10:27 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "expansions.h"

void	copy_expansion_to_string(char *dst, t_Expansion *expansion,
								ssize_t *lex_i)
{
	size_t	exp_i;

	exp_i = 0;
	expansion->start = &dst[*lex_i];
	while (exp_i < expansion->value->len)
	{
		dst[*lex_i] = expansion->value->start[exp_i];
		(*lex_i)++;
		exp_i++;
	}
	expansion->end = &dst[*lex_i - 1];
}

void	copy_old_to_new(char *dst, char *dst_end,
						char *src, t_Expansion_List *expansions)
{
	ssize_t		i;
	size_t		j;
	t_Expansion	*expansion;

	i = 0;
	j = 0;
	expansion = get_next_expansion(expansions, GET);
	while (&dst[i] < dst_end)
	{
		if (expansion && i == expansion->offset)
		{
			copy_expansion_to_string(dst, expansion, &i);
			if (expansion == expansions->tail)
				j += expansion->key->len;
			else
				j += expansion->value->len;
			expansion = get_next_expansion(expansions, GET);
		}
		else
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
}

void	update_token_lexeme(t_Token *token, t_Expansion_List *expansions)
{
	t_String	*new_lexeme;

	new_lexeme = string(calculate_unexpanded_len(token, token->lex)
			+ expansions->tail->value->len);
	copy_old_to_new(new_lexeme->start, new_lexeme->end,
		token->lex->start, expansions);
	token->lex = new_lexeme;
	token->lexeme = token->lex->start;
	token->quotes = find_quoted_sections(token, expansions);
}
