/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:47:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/10 04:31:46 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "tokens.h"
#include "lexer.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

/* 	I WILL READ THE DOCUMENTATION AND HANDLE QUOTES PROPERLY THIS TIME */

/**
 * \ - An unquoted backslash escapes the next character, preserving its
 *		literal value. If the backslash precedes a newline, treat it as a line
 *		continuation and continue prompting.
 *	'' - Strong quotes. Preserves the literal value of each character within.
 *	"" - Weak quotes. Preserves literal values of characters other than
 *			dollar signs, backslashes and backticks.
 **/

#include <stdio.h>

bool	is_delimiter(const char c, const char *delims)
{
	while (*delims != '\0')
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

void	update_lexer_state(t_Lexer *lexer);
t_Line	*get_input_line(int fd);
void	handle_unterminated_input(t_Lexer *lexer);

#define DELIMITERS " \t\n|&;()<>"

/**
* At this point, all operators have been checked for. The remaining token
* can only be a word, where quotes and escapes have to be handled carefully.
*/
void	match_word(t_Lexer *lexer, t_Token_list *tokens)
{
	while (*lexer->end_char != '\0')
	{
		update_lexer_state(lexer);
		if (lexer->state == UNQUOTED)
		{
			if (!is_delimiter(*lexer->end_char, DELIMITERS))
			{
				lexer->end_char++;
				continue ;
			}
			else if (is_delimiter(*lexer->end_char, DELIMITERS))
			{
				lexer->end_char--;
				break ;
			}
		}
		else if (lexer->state == WEAK_QUOTE)
		{
			while (*lexer->end_char && *lexer->end_char != '"')
				lexer->end_char++;
		}
	}
	if (lexer->terminated)
	{
		add_token(tokens, create_token(WORD, extract_substring(lexer->start_char, lexer->end_char)));
		lexer->start_char = lexer->end_char + 1;
		lexer->end_char = lexer->start_char;
	}
	else if (lexer->terminated == false)
	{
		handle_unterminated_input(lexer);
		match_word(lexer, tokens);
	}
}

void	join_input_lines(t_Lexer *lexer, t_Input *input)
{
	int		offset;
	char	*joined;

	offset = lexer->end_char - lexer->line->start;
	joined = ft_strjoin(lexer->line->start, input->lines[input->count - 1]->start);
	lexer->line = make_line(joined);
	// lexer->start_char = &joined[offset];
	lexer->start_char = lexer->line->start;
	lexer->end_char = &joined[offset];
}

void	handle_unterminated_input(t_Lexer *lexer)
{
	t_Line	*next_line; (void)lexer;

	write(STDERR_FILENO, "> ", 2);
	next_line = get_input_line(STDIN_FILENO);
	store_input(&lexer->input, next_line);
	join_input_lines(lexer, &lexer->input);
}

void	update_lexer_state(t_Lexer *lexer)
{
	const char	*curr = lexer->end_char;

	if (lexer->state == UNQUOTED)
	{
		if (*curr == '"')
		{
			lexer->state = WEAK_QUOTE;
			lexer->terminated = false;
			lexer->end_char++;
			curr++;
		}
	}
	else if (lexer->state == WEAK_QUOTE)
	{
		if (*curr == '"')
		{
			lexer->state = UNQUOTED;
			lexer->terminated = true;
		}
	}
	else if (lexer->state == STRONG_QUOTE)
		;

}

