/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:33:03 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:03:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static size_t	calculate_new_len(t_String *lexeme, t_Quote_List *quotes);

void	quote_removal(t_Token *token)
{
	char		*s;
	t_String	*new_lexeme;
	size_t		new_len;
	size_t		i;

	if (token->quotes.pair_count == 0)
		return ;
	new_len = calculate_new_len(token->lex, &token->quotes);
	new_lexeme = string(new_len);
	s = token->lex->start;
	i = 0;
	while (s && s < token->lex->end && *s)
	{
		if (quote_to_remove(&token->quotes, s))
			s++;
		else
		{
			new_lexeme->start[i] = *s;
			s++;
			i++;
		}
	}
	string_free(token->lex);
	token->lex = new_lexeme;
}

static size_t	calculate_new_len(t_String *lexeme, t_Quote_List *quotes)
{
	char	*s;
	size_t	len;

	s = lexeme->start;
	len = 0;
	while (s && s < lexeme->end && *s)
	{
		if (quote_to_remove(quotes, s))
			s++;
		else
		{
			len++;
			s++;
		}
	}
	return (len);
}
