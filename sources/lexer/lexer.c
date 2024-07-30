/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:58:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 11:43:27 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "tokens.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static void
init_lexer(t_Lexer *lexer, t_Input *input);

static void
init_matches(t_Match_Table (*matches)[OP_TOKENS]);

static bool	
end_of_line(t_Token *token);

/*
 * With the line read from the prompt, start scanning through it to tokenize.
 * Returns a list of all the tokens.
 */
t_Token_List	scan(t_Input *input)
{
	t_Lexer			lexer;
	t_Token_List	tokens;

	init_lexer(&lexer, input);
	tokens = (t_Token_List){.head = NULL, .tail = NULL};
	while (input->ok && !end_of_line(tokens.tail))
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
 * Initializes the state of the lexer.
 * Originally trying to implement handling unclosed quotes and
 * multiple lines of inputs, but it doesn't work quite right
 * and I have given up.
 **/
static void	init_lexer(t_Lexer *lexer, t_Input *input)
{
	lexer->line = input->lines[0];
	lexer->start = lexer->line->start;
	lexer->end = lexer->start;
	lexer->state = UNQUOTED;
	lexer->terminated = true;
}

/**
 * Goes through the match table, creating a token of the corresponding type
 * when a match is found
 * If no match found, it is a WORD token
**/
void	match(t_Input *input, t_Lexer *lexer, t_Token_List *tokens)
{
	static t_Match_Table	matches[OP_TOKENS];
	t_Match_Table const		*match;
	t_Token					*new_token;
	int						i;

	if (matches[0].lexeme == NULL)
		init_matches(&matches);
	i = 0;
	while (i < OP_TOKENS)
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
static void	init_matches(t_Match_Table (*matches)[OP_TOKENS])
{
	const t_Match_Table	temp[OP_TOKENS] = {
	{"\n", END_OF_LINE},
	{"||", OR_OR},
	{"|", PIPE},
	{"&&", AND_AND},
	{"<<", LESSER_LESSER},
	{"<", LESSER},
	{">>", GREATER_GREATER},
	{">", GREATER},
	{"(", OPEN_PARAN},
	{")", CLOSE_PARAN},
	};

	ft_memcpy(matches, temp, sizeof(temp));
}
