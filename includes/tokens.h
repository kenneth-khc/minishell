/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:25:32 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:19:51 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "quotes.h"

/**
 * Types of tokens the shell recognizes. They are either a word, or an
 * operator that performs special functions. 
 * A word is defined as a sequence of characters that is delimited by blanks
 * and metacharacters, unless the blanks and metacharacters are quoted.
 **/

# define TOKEN_COUNT 13
# define OP_TOKENS 10

enum e_Token_Types
{
/* WORD tokens */
	WORD = 256,
	ASSIGNMENT_WORD,
	IO_NUMBER,
/* Operator tokens */
	// |
	PIPE,
	// ||
	OR_OR,
	// &&
	AND_AND,
	// <
	LESSER,
	// <<
	LESSER_LESSER,
	// >
	GREATER,
	// >>
	GREATER_GREATER,
	// (
	OPEN_PARAN,
	// )
	CLOSE_PARAN,
	// \n
	END_OF_LINE,
	// \0
	END_OF_INPUT
};

/**
 * Representing a token.
 * Stores the type of the token and its lexeme.
 * Points to the next token in the list.
 */
typedef struct s_Token
{
	enum e_Token_Types	type;
	char				*lexeme;
	int					word_flags;
	t_Quote_List		quotes;
	struct s_Token		*next;
	struct s_Token		*prev;
}	t_Token;

# define W_STRONG_QUOTED	       0b1
# define W_WEAK_QUOTED	      0b10
# define W_PARAM_EXPANSION  0b100
# define W_TILDE_EXPANSION 0b1000

/**
 * A list of all the tokens.
 * Terminated by an END_OF_LINE token when end of input is reached.
 */
typedef struct s_Token_List
{
	struct s_Token	*head;
	struct s_Token	*tail;
}	t_Token_List;

t_Token			*create_token(int type, const char *lexeme);
void			add_token(t_Token_List *tokens, t_Token *token);
void			free_tokens(t_Token_List *tokens);
t_Quote_List	find_quotes(t_Token *token);

#endif
