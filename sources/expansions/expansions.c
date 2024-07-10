/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/10 18:04:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "a.h"
#include "libft.h"
#include "tokens.h"
#include "expansions.h"

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
		if (only_digits(tok->lexeme) && is_redirection_token(tok->next))
		{
			// check for max fd
			// printf("word: %s\n", tok->lexeme);
			// printf("was %s\n", token_enum_to_str(tok));
			tok->type = IO_NUMBER;
			// printf("now io_number\n\n");
		}
		tok = tok->next;
	}
}

void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	find_io_number(tokens);
	tilde_expansion(tokens, env);
	parameter_expansion(tokens, env);
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

