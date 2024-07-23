/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 11:12:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "expansions.h"
#include "tokens.h"

bool	only_digits(const char *str);

//TODO: wildcards (filename expansion)
void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token	*token;

	token = tokens->head;
	while (token)
	{
		tilde_expansion(token, env);
		if (parameter_expand(token, env))
		{
			word_splitting(token, tokens);
		}
		token = token->next;
	}
}

// Internal field seperator should default to whitespaces
#ifndef IFS
//# define IFS " \t\n"
# define IFS ' '
#endif

void	split_token_to_tokens(t_Token_List *tokens, t_Token *token,
			t_Token_List *new_tokens)
{
	if (new_tokens->tail)
	{
		new_tokens->tail->next = token->next;
		if (token->prev)
			token->prev->next = new_tokens->head;
		else
			tokens->head = new_tokens->head;
		if (token->next)
			token->next->prev = new_tokens->tail;
		else
			tokens->tail = new_tokens->tail;
	}
}

void	word_splitting(t_Token *token, t_Token_List *tokens)
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
	free(w);
	split_token_to_tokens(tokens, token, &new_tokens);
}

void	tilde_expansion(t_Token *token, t_entab *env)
{
	if (token->word_flags & W_TILDE_EXPANSION)
		token->lexeme = ft_strdup(get_var("HOME", env)->val);
}
