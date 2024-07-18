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
		.start_char = line->start,
		.end_char = line->start,
		.state = UNQUOTED,
		.terminated = true};
	tokens = (t_Token_List){.head = NULL, .tail = NULL};
	while (!end_of_line(tokens.tail))
	{
		while (is_blank(*lexer.start_char))
		{
			lexer.start_char++;
			lexer.end_char++;
		}
		match(input, &lexer, &tokens);
	}
	return (tokens);
}

void	match(t_Input *input, t_Lexer *lexer, t_Token_List *tokens)
{
	int						i;
	t_Match_Table const		*match;
	static t_Match_Table	matches[TOKEN_TYPES];
	t_Token					*new_token;

	if (matches[0].lexeme == NULL)
		init_matches(&matches);
	i = 0;
	while (i < TOKEN_TYPES)
	{
		match = &matches[i];
		if (ft_strncmp(lexer->start_char, match->lexeme,
				ft_strlen(match->lexeme)) == 0)
		{
			new_token = create_token(match->type, ft_strdup(match->lexeme));
			add_token(tokens, new_token);
			lexer->start_char += ft_strlen(match->lexeme);
			lexer->end_char = lexer->start_char;
			return ;
		}
		i++;
	}
	match_word(lexer, tokens, input);
}

bool	end_of_line(t_Token *token)
{
	return (token && token->type == END_OF_LINE && token->next == NULL);
}

void	init_matches(t_Match_Table (*matches)[TOKEN_TYPES])
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
