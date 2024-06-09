/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:58:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/10 01:50:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/*
 * With the line read from the prompt, start scanning through it to tokenize.
 * Returns a list of all the tokens.
 */
t_Token_list	scan(t_Input *input)
{
	t_Line	*line = input->lines[0];
	t_Lexer			lexer;
	t_Token_list	tokens;

	lexer = (t_Lexer){.line = line,
		// .start = line->start,
		// .lookahead = *line,
		.start_char = line->start,
		.end_char = line->start,
		.state = UNQUOTED,
		.terminated = true,
		.history = &line->start};
	store_input(&lexer.input, line);
	tokens = (t_Token_list){.head = NULL, .tail = NULL};
	while (!end_of_line(tokens.tail))
	{
		while (is_blank(*lexer.start_char))
		{
			lexer.start_char++;
			lexer.end_char++;
		}
		match(&lexer, &tokens);
	}
	return (tokens);
}

void	match(t_Lexer *lexer, t_Token_list *tokens)
{
	int	i = 0;
	t_Match_Table const *ptr;
	static t_Match_Table	matches[TOKEN_TYPES] = {
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

	while (i < TOKEN_TYPES)
	{
		ptr = &matches[i];
		if (ft_strncmp(lexer->start_char, ptr->lexeme, ft_strlen(ptr->lexeme)) == 0)
		{
			add_token(tokens, create_token(ptr->type, ptr->lexeme));
			lexer->start_char += ft_strlen(ptr->lexeme);
			lexer->end_char = lexer->start_char;
			return ;
		}
		i++;
	}
	match_word(lexer, tokens);
}

bool	end_of_line(t_Token *token)
{
	return (token && token->type == END_OF_LINE);
}

