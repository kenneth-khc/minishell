/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:47:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 05:50:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "execution.h"
#include "libft.h"
#include "ft_dprintf.h"
#include "get_next_line.h"
#include "tokens.h"
#include "lexer.h"
#include "definitions.h"

/**
 * \ - An unquoted backslash escapes the next character, preserving its
 *		literal value. If the backslash precedes a newline, treat it as a line
 *		continuation and continue prompting.
 *	'' - Strong quotes. Preserves the literal value of each character within.
 *	"" - Weak quotes. Preserves literal values of characters other than
 *			dollar signs, backslashes and backticks.
 **/

/**
* At this point, all operators have been checked for. The remaining token
* can only be a word, where quotes and escapes have to be handled carefully.
**/
void	match_word(t_Lexer *lexer, t_Token_List *tokens, t_Input *input)
{
	char		*lexeme;

	advance_word(lexer);
	if (lexer->terminated)
	{
		lexeme = ft_extract_substring(lexer->start, lexer->end);
		if (io_number(lexeme, lexer->end + 1))
			add_token(tokens, create_token(IO_NUMBER, lexeme));
		else
			add_token(tokens, create_token(WORD, lexeme));
		set_word_flags(tokens->tail);
		tokens->tail->quotes = find_quotes(tokens->tail);
		lexer->start = lexer->end + 1;
		lexer->end = lexer->start;
	}
	else if (lexer->terminated == false)
	{
		input->ok = false;
		ft_dprintf(STDERR_FILENO, "input error: unclosed quotes\n");
		set_exit_status(2);
	}
}

void	advance_word(t_Lexer *lexer)
{
	while (*lexer->end != '\0')
	{
		update_lexer_state(lexer);
		if (lexer->state == UNQUOTED)
		{
			if (!is_metacharacter(*lexer->end))
			{
				lexer->end++;
				continue ;
			}
			else if (is_metacharacter(*lexer->end))
			{
				lexer->end--;
				break ;
			}
		}
		else if (lexer->state == WEAK_QUOTE)
			while (*lexer->end && *lexer->end != '"')
				lexer->end++;
		else if (lexer->state == STRONG_QUOTE)
			while (*lexer->end && *lexer->end != '\'')
				lexer->end++;
	}
}

void	update_lexer_lines(t_Lexer *lexer, t_Input *input)
{
	size_t		start_offset;
	size_t		end_offset;
	t_String	*complete_input;

	start_offset = lexer->start - lexer->line->start;
	end_offset = lexer->end - lexer->line->start;
	complete_input = lines_to_string(input);
	lexer->line = complete_input;
	lexer->start = lexer->line->start + start_offset;
	lexer->end = lexer->line->start + end_offset;
}

/**
 * Transition into different states based on the current character.
 * When word is unquoted, metacharacters delimit it.
 * When word is quoted, its corresponding end quote delimits it.
**/
void	update_lexer_state(t_Lexer *lexer)
{
	const char	*curr = lexer->end;
	static char	terminator;

	if (lexer->state == UNQUOTED)
	{
		if (is_quote(*curr))
		{
			if (*curr == '\'')
				lexer->state = STRONG_QUOTE;
			else if (*curr == '"')
				lexer->state = WEAK_QUOTE;
			lexer->terminated = false;
			lexer->end++;
		}
		terminator = *curr;
	}
	else if (lexer->state == WEAK_QUOTE
		|| lexer->state == STRONG_QUOTE)
	{
		if (*curr == terminator)
		{
			lexer->state = UNQUOTED;
			lexer->terminated = true;
		}
	}
}

void	set_word_flags(t_Token *token)
{
	const char	*word;
	const char	*eq;

	word = token->lexeme;
	if (ft_strchr(word, '='))
	{
		eq = ft_strchr(word, '=');
		if (is_valid_name(word, eq))
			token->type = ASSIGNMENT_WORD;
	}
	if (ft_strchr(word, '~') && ft_strlen(word) == 1)
		token->word_flags |= W_TILDE_EXPANSION;
}
