/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 00:16:42 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expansions.h"
#include "libft.h"
#include "tokens.h"
#include <stdlib.h>
#include <unistd.h>

bool	only_digits(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

#include "parser.h"
void	find_io_number(t_Token_List *tokens)
{
	t_Token	*tok;

	tok = tokens->head;
	while (tok != NULL)
	{
		if (only_digits(tok->lexeme)
			&& is_redirection_token(tok->next)
			&& ft_atoi(tok->lexeme) < OPEN_MAX)
		{
			tok->type = IO_NUMBER;
		}
		tok = tok->next;
	}
}

void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	find_io_number(tokens);
	tilde_expansion(tokens, env);
	parameter_expansion(tokens, env);
	quote_removal(tokens);
}

void	tilde_expansion(t_Token_List *tokens, t_entab *env)
{
	t_Token	*curr;

	curr = tokens->head;
	while (curr != NULL)
	{
		if (curr->word_flags & W_TILDE_EXPANSION)
		{
			curr->lexeme = ft_strdup(get_var("HOME", env)->val);
		}
		curr = curr->next;
	}
}

// todo: word splitting
// todo: filename expansion (*)
// todo: pattern matching
// todo: quote removal

void	quote_removal(t_Token_List *tokens)
{
	t_Token	*tok;
	char	*to_free;

	tok = tokens->head;
	while (tok)
	{
		if (tok->word_flags & W_WEAK_QUOTED
			|| tok->word_flags & W_STRONG_QUOTED)
		{
			to_free = (char *)tok->lexeme;
			tok->lexeme = ft_extract_substring(tok->lexeme + 1,
									  tok->lexeme + ft_strlen(tok->lexeme) - 2);
			free(to_free);
		}
		tok = tok->next;
	}
}

