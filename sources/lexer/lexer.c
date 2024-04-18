/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:58:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:41:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

t_Token_list	scan(char **line)
{
	t_Token_list	tokens;
	t_Lexer			scanner;

	tokens = (t_Token_list){.head = NULL, .tail = NULL};
	scanner.line = *line;
	scanner.start = *line;
	scanner.lookahead = *line;
	scanner.history = line;
	t_Matcher *matchers = init_matchers();
	while (!end_of_line(tokens.tail))
	{
		skip_whitespaces(&scanner);
		match(&scanner, matchers, &tokens);
	}
	return (tokens);
}

void	match(t_Lexer *scanner, t_Matcher *matchers, t_Token_list *tokens)
{
	int	i;

	i = 0;
	while (i < TOKEN_MATCHERS)
	{
		if (*scanner->start == matchers[i].start)
		{
			matchers[i].match_function(scanner, tokens);
			break ;
		}
		i++;
		if (i == TOKEN_MATCHERS - 1)
			match_word(scanner, tokens);
	}
}

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
	matchers[4].start = '\n';
	matchers[4].match_function = match_end_of_line;
	matchers[5].start = '#';
	matchers[5].match_function = skip_comment;
	// matchers[4].start = '\'';
	// matchers[4].match_function = match_quotes;
	// matchers[5].start = '\'';
	// matchers[5].match_function = match_quotes;
	return (matchers);
}

bool	end_of_line(t_Token *token)
{
	return (token && token->type == END_OF_LINE);
}

void	skip_whitespaces(t_Lexer *scanner)
{
	while (is_blank(*scanner->lookahead))
		scanner->lookahead++;
	scanner->start = scanner->lookahead;
}

