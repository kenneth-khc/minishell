/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:52 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:39:35 by kecheong         ###   ########.fr       */
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
	ESCAPE
} t_Word_State;

typedef struct s_Lexer
{
	t_Line			*line; // the current line being processed
	char			*start_char; // start of the token to be grabbed
	char			*end_char; // end of the token to be grabbed
	t_Word_State	state; // whether it is currently unquoted or quoted
	bool			terminated; // are quotes properly terminated
}	t_Lexer;

typedef struct s_Match_Table
{
	const char			*lexeme;
	enum e_Token_Types	type;
}	t_Match_Table;

bool	is_metacharacter(const char c);
bool	is_blank(const char c);
char	*extract_substring(const char *start, const char *end);
bool	end_of_line(t_Token *token);
void	skip_comment(t_Lexer *lexer);
void	match(t_Input *input, t_Lexer *lexer, t_Token_List *tokens);

/* Words */
void	match_word(t_Lexer *lexer, t_Token_List *tokens, t_Input *input);
void	advance_word(t_Lexer *lexer);
void	join_input_lines(t_Lexer *lexer, t_Input *input);
void	update_lexer_state(t_Lexer *lexer);

#endif
