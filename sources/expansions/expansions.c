/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 21:01:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "expansions.h"
#include "tokens.h"
#include "parser.h"

static void	io_number(t_Token *token);
static bool	only_digits(const char *str);

void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token	*token;

	token = tokens->head;
	while (token)
	{
		io_number(token);
		tilde_expansion(token, env);
		if (parameter_expand(token, env))
		{
			word_splitting(token);
		}
		// todo: filename expansion
		filename_expansion(token, env);
		token = token->next;
	}
}

// Internal field seperator should default to whitespaces
#ifndef IFS
//# define IFS " \t\n"
# define IFS ' '
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
	if (new_tokens.tail)
	{
		new_tokens.tail->next = token->next;
		if (token->prev)
		{
			token->prev->next = new_tokens.head;
		}
		if (token->next)
		{
			token->next->prev = new_tokens.tail;
		}
	}
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

/**
 * Looks at a token before a redirection operator,
 * if it only consists of numbers and is within fd range
 * it is a file descriptor.
**/
static void	io_number(t_Token *token)
{
	if (only_digits(token->lexeme)
		&& is_redirection_token(token->next)
		&& ft_atoi(token->lexeme) < OPEN_MAX)
	{
		token->type = IO_NUMBER;
	}
}

static bool	only_digits(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
