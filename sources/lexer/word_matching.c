/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:47:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/15 22:07:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

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
	t_Token	*word;
	char	*lexeme;
	t_Line	*next_line;

	advance_word(lexer);
	if (lexer->terminated)
	{
		lexeme = ft_extract_substring(lexer->start_char, lexer->end_char);
		word = create_token(WORD, lexeme);
		add_token(tokens, word);
		set_word_flags(word);
		// if (word->word_flags & W_ASSIGNMENT)
		// 	printf("assign\n");
		// else
		// 	printf("no assign\n");
		lexer->start_char = lexer->end_char + 1;
		lexer->end_char = lexer->start_char;
	}
	else if (lexer->terminated == false)
	{
		write(STDERR_FILENO, "> ", 2);
		next_line = get_input_line(STDIN_FILENO);
		store_input(input, next_line);
		join_input_lines(lexer, input);
		match_word(lexer, tokens, input);
	}
}

void	advance_word(t_Lexer *lexer)
{
	while (*lexer->end_char != '\0')
	{
		update_lexer_state(lexer);
		if (lexer->state == UNQUOTED)
		{
			if (!is_metacharacter(*lexer->end_char))
			{
				lexer->end_char++;
				continue ;
			}
			else if (is_metacharacter(*lexer->end_char))
			{
				lexer->end_char--;
				break ;
			}
		}
		else if (lexer->state == WEAK_QUOTE)
			while (*lexer->end_char && *lexer->end_char != '"')
				lexer->end_char++;
		else if (lexer->state == STRONG_QUOTE)
			while (*lexer->end_char && *lexer->end_char != '\'')
				lexer->end_char++;
	}
}

void	join_input_lines(t_Lexer *lexer, t_Input *input)
{
	int		offset;
	char	*joined;

	offset = lexer->end_char - lexer->line->start;
	joined = ft_strjoin(lexer->line->start,
			input->lines[input->count - 1]->start);
	lexer->line = make_line(joined);
	lexer->start_char = lexer->line->start;
	lexer->end_char = &joined[offset];
}

/**
 * Transition into different states based on the current character.
 * When word is unquoted, metacharacters delimit it.
 * When word is quoted, its corresponding end quote delimits it.
**/
void	update_lexer_state(t_Lexer *lexer)
{
	const char	*curr = lexer->end_char;
	static char	terminator;

	if (lexer->state == UNQUOTED)
	{
		if (*curr == '"')
		{
			lexer->state = WEAK_QUOTE;
			lexer->terminated = false;
			lexer->end_char++;
		}
		else if (*curr == '\'')
		{
			lexer->state = STRONG_QUOTE;
			lexer->terminated = false;
			lexer->end_char++;
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

#include "debug.h"
#include "quotes.h"
void	set_word_flags(t_Token *token)
{
	const char	*word;
	//const char	*word_end;
	const char	*eq;

	word = token->lexeme;
	//word_end = word + ft_strlen(word) - 1;
	token->quotes = find_quotes(token);
	//print_quote_list(token);
	if (ft_strchr(word, '$'))
		token->word_flags |= W_HAS_DOLLAR;
	if (ft_strchr(word, '='))
	{
		eq = ft_strchr(word, '=');
		if (is_valid_name(word, eq))
		{
			token->word_flags |= W_ASSIGNMENT;
			token->type = ASSIGNMENT_WORD;
		}
	}
	if (ft_strchr(word, '~') && ft_strlen(word) == 1)
		token->word_flags |= W_TILDE_EXPANSION;
}

#include "expansions.h"
bool	is_valid_name(const char *start, const char *end)
{
	while (start < end)
	{
		if (is_not_identifier(*start))
		// if (!ft_isalnum(*start) && *start != '_')
			return (false);
		start++;
	}
	return (true);
}

