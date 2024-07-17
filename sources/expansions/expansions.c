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
		parameter_expand(token, env);
		// do word split
		token = token->next;
	}
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

