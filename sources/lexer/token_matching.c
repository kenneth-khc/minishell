/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_matching.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:06:35 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/15 21:11:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "errors.h"

t_Matcher	*init_matchers(void)
{
	t_Matcher	*matchers;

	matchers = malloc(sizeof(*matchers) * TOKEN_MATCHERS);
	matchers[0].start = '|';
	matchers[0].match_function = match_bar;
	matchers[1].start = '<';
	matchers[1].match_function = match_lesser;
	matchers[2].start = '>';
	matchers[2].match_function = match_greater;
	matchers[3].start = '&';
	matchers[3].match_function = match_and;
	matchers[4].start = '\0';
	matchers[4].match_function = match_end_of_line;
	// matchers[4].start = '\'';
	// matchers[4].match_function = match_quotes;
	// matchers[5].start = '\'';
	// matchers[5].match_function = match_quotes;
	return (matchers);
}

void	match_bar(t_Lexer *scanner, t_Token_list *tokens)
{
	scanner->lookahead++;
	if (*scanner->lookahead == '|')
	{
		add_token(tokens, create_token(OR_OR, "||"));
		scanner->start += 2;
	}
	else
	{
		add_token(tokens, create_token(PIPE, "|"));
		scanner->start += 1;
	}
	scanner->lookahead = scanner->start;
}

void	match_lesser(t_Lexer *scanner, t_Token_list *tokens)
{
	scanner->lookahead++;
	if (*scanner->lookahead == '<')
	{
		add_token(tokens, create_token(LESSER_LESSER, "<<"));
		scanner->start += 2;
	}
	else
	{
		add_token(tokens, create_token(LESSER, "<"));
		scanner->start += 1;
	}
	scanner->lookahead = scanner->start;
}

void	match_greater(t_Lexer *scanner, t_Token_list *tokens)
{
	scanner->lookahead++;
	if (*scanner->lookahead == '>')
	{
		add_token(tokens, create_token(GREATER_GREATER, ">>"));
		scanner->start += 2;
	}
	else
	{
		add_token(tokens, create_token(GREATER, ">"));
		scanner->start += 1;
	}
	scanner->lookahead = scanner->start;
}

void	match_and(t_Lexer *scanner, t_Token_list *tokens)
{
	scanner->lookahead++;
	if (*scanner->lookahead == '&')
	{
		add_token(tokens, create_token(AND_AND, "&&"));
		scanner->start += 2;
	}
	else
	{
		error("unexpected token `&`");
	}
	scanner->lookahead = scanner->start;
}
