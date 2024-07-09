/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:47:44 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/26 23:49:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "ft_dprintf.h"

// Checks if a token is for redirection
bool	is_redirection_token(t_Token *token)
{
	if (token)
	{
		return (token->type == LESSER ||
			token->type == LESSER_LESSER ||
			token->type == GREATER ||
			token->type == GREATER_GREATER);
	}
	return (false);
}

bool	is_and_or(t_Parser *parser)
{
	return (peek(1, parser) == AND_AND
			|| peek(1, parser) == OR_OR);
}

enum e_Token_Types	peek(int k, t_Parser *parser)
{
	t_Token	*curr;

	if (k > 0 && k <= get_tokens_count(parser->tokens))
	{
		curr = parser->token;
		while (k > 1)
		{
			curr = curr->next;
			k--;
		}
		return (curr->type);
	}
	return (0);
}

void	consume(t_Parser *parser)
{
	if (parser->token)
	{
		parser->token = parser->token->next;
	}
}

bool	accept(t_Parser *parser, enum e_Token_Types type)
{
	if (parser->token->type == type)
	{
		consume(parser);
		return (true);
	}
	return (false);
}

bool	expect(t_Parser *parser, enum e_Token_Types expected)
{
	if (accept(parser, expected))
	{
		return (true);
	}
	ft_dprintf(STDERR_FILENO, "unexpected token %d\n", parser->token->type);
	return (false);
}
