/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_matching.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:06:35 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:40:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "errors.h"

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
