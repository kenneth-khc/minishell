/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:58:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/10 17:55:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "tokens.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static void	init_matches(t_Match_Table (*matches)[TOKEN_TYPES]);
static bool	end_of_line(t_Token *token);

/*
 * With the line read from the prompt, start scanning through it to tokenize.
 * Returns a list of all the tokens.
 */
t_Token_List	scan(t_Input *input)
{
	t_Line			*line;
	t_Lexer			lexer;
	t_Token_List	tokens;

	line = input->lines[0];
	lexer = (t_Lexer){.line = line,
		.start = line->start,
		.end = line->start,
		.state = UNQUOTED,
		.terminated = true};
	tokens = (t_Token_List){.head = NULL, .tail = NULL};
	while (!end_of_line(tokens.tail))
	{
		while (is_blank(*lexer.start))
		{
			lexer.start++;
			lexer.end++;
		}
		match(input, &lexer, &tokens);
	}
	return (tokens);
}

/**
 * Goes through the match table, creating a token of the corresponding type
 * when a match is found
 * If no match found, it is a WORD token
**/
void	match(t_Input *input, t_Lexer *lexer, t_Token_List *tokens)
{
	static t_Match_Table	matches[TOKEN_TYPES];
	t_Match_Table const		*match;
	t_Token					*new_token;
	int						i;

	if (matches[0].lexeme == NULL)
		init_matches(&matches);
	i = 0;
	while (i < TOKEN_TYPES)
	{
		match = &matches[i];
		if (ft_strncmp(lexer->start, match->lexeme,
				ft_strlen(match->lexeme)) == 0)
		{
			new_token = create_token(match->type, ft_strdup(match->lexeme));
			add_token(tokens, new_token);
			lexer->start += ft_strlen(match->lexeme);
			lexer->end = lexer->start;
			return ;
		}
		i++;
	}
	match_word(lexer, tokens, input);
}

static bool	end_of_line(t_Token *token)
{
	return (token && token->type == END_OF_LINE && token->next == NULL);
}

/**
 * Only called the first time to initialize the match table
**/
static void	init_matches(t_Match_Table (*matches)[TOKEN_TYPES])
{
	const t_Match_Table	temp[TOKEN_TYPES] = {
	{"\n", END_OF_LINE},
	{"||", OR_OR},
	{"|", PIPE},
	{"&&", AND_AND},
	{"<<", LESSER_LESSER},
	{"<", LESSER},
	{">>", GREATER_GREATER},
	{">", GREATER},
	{"*", STAR},
	{"(", OPEN_PARAN},
	{")", CLOSE_PARAN},
	{";", SEMICOLON},
	{"#", HASH}
	};

	ft_memcpy(matches, temp, sizeof(temp));
}
