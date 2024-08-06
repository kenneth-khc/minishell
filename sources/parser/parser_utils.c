/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:47:44 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 18:22:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_dprintf.h"
#include "tokens.h"
#include "parser.h"

/**
 * Lookahead 1 in the token stream
**/
enum e_Token_Types	peek(t_Parser *parser)
{
	if (parser->token)
		return (parser->token->type);
	else
		return (0);
}

/**
 * If the token is not what we expected, throw a syntax error
 **/
bool	expect(t_Parser *parser, enum e_Token_Types expected,
			const char *errmsg)
{
	if (peek(parser) == expected)
		return (true);
	else
	{
		syntax_error(parser, errmsg, parser->token);
		return (false);
	}
}

/**
 * Advance 1 through the token stream
 * Keep track of the just consumed token for error reporting
**/
t_Token	*consume(t_Parser *parser)
{
	if (parser->token)
	{
		parser->consumed = parser->token;
		parser->token = parser->token->next;
		return (parser->token->prev);
	}
	else
		return (NULL);
}

/**
 * If the current token is what we want, consume it else return false
**/
bool	accept(t_Parser *parser, enum e_Token_Types type)
{
	if (peek(parser) == type)
	{
		consume(parser);
		return (true);
	}
	else
		return (false);
}

void	set_exit_status(int status);

#define EXIT_SYNTAX_ERROR 2

/**
 * If a syntax error is found, print a descriptive error message to stderr
 * for the user
 * Only the first syntax error found is printed
**/
void	syntax_error(t_Parser *parser, const char *err_msg, t_Token *got)
{
	const char	*symbol;

	if (parser->syntax_ok)
	{
		ft_dprintf(STDERR_FILENO, "%s: syntax error: %s", SHELL, err_msg);
		if (got)
		{
			if (got->type == END_OF_LINE)
				symbol = "newline";
			else
				symbol = got->lex->start;
			ft_dprintf(STDERR_FILENO, ", got `%s` instead", symbol);
		}
		ft_dprintf(STDERR_FILENO, "\n");
		parser->syntax_ok = false;
	}
	set_exit_status(EXIT_SYNTAX_ERROR);
	return ;
}
