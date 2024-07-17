/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 10:40:02 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expansions.h"
#include "libft.h"
#include "tokens.h"
#include <stdlib.h>
#include <unistd.h>

#include "parser.h"
void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token	*token;

	token = tokens->head;
	while (token)
	{
		io_number(token);
		tilde_expansion(token, env);
		if (parameter_expand(token, env))
			word_splitting(token);
		token = token->next;
	}
}

#ifndef IFS
#define IFS " \t\n"
#endif
#include <stdio.h>
void	word_splitting(t_Token *token)
{
	char			**words;
	char			**w;
	t_Token_List	new_tokens;
	t_Token			*new_token;

	new_tokens = (t_Token_List){.head = NULL, .tail = NULL};
	words = ft_split(token->lexeme, ' ');
	if (words == NULL)
		return ;
	w = words;
	while (*words)
	{
		new_token = create_token(WORD, *words);
		add_token(&new_tokens, new_token);
		words++;
	}
	new_tokens.tail->next = token->next;
	token->prev->next = new_tokens.head;
	token->next->prev = new_tokens.tail;
	free(w);
}

void	tilde_expansion(t_Token *token, t_entab *env)
{
	if (token->word_flags & W_TILDE_EXPANSION)
		token->lexeme = ft_strdup(get_var("HOME", env)->val);
}

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif
void	io_number(t_Token *token)
{
	if (only_digits(token->lexeme)
		&& is_redirection_token(token->next)
		&& ft_atoi(token->lexeme) < OPEN_MAX)
	{
		token->type = IO_NUMBER;
	}
}

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

