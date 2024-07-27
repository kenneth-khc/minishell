/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:52 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 05:49:12 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stddef.h>
# include "tokens.h"
# include "input.h"

typedef enum e_Word_State
{
	UNQUOTED,
	WEAK_QUOTE,
	STRONG_QUOTE,
}	t_Word_State;

typedef struct s_Lexer
{
	t_String		*line; // the current line being processed
	char			*start; // start of the token to be grabbed
	char			*end; // end of the token to be grabbed
	t_Word_State	state; // whether it is currently unquoted or quoted
	bool			terminated; // are quotes properly terminated
}	t_Lexer;

typedef struct s_Match_Table
{
	const char			*lexeme;
	enum e_Token_Types	type;
}	t_Match_Table;

t_Token_List	scan(t_Input *input);
bool			is_metacharacter(const char c);
bool			is_blank(const char c);
void			skip_comment(t_Lexer *lexer);
void			match(t_Input *input, t_Lexer *lexer, t_Token_List *tokens);

/* Words */
void			match_word(t_Lexer *lexer, t_Token_List *tokens,
					t_Input *input);
void			advance_word(t_Lexer *lexer);
void			join_input_lines(t_Lexer *lexer, t_Input *input);
void			update_lexer_state(t_Lexer *lexer);
void			update_lexer_lines(t_Lexer *lexer, t_Input *input);
bool			io_number(char *lexeme, char *delim);

void			set_word_flags(t_Token *token);
bool			is_valid_name(const char *start, const char *end);

#endif
