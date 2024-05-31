/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:47:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:53:28 by kecheong         ###   ########.fr       */
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
typedef enum e_Word_State
{
	UNQUOTED,
	WEAK_QUOTE,
	STRONG_QUOTE,
	ESCAPE
} t_Word_State;

#include <stdio.h>
void	check_state(t_Word_State state)
{
	printf("State: ");
	if (state == UNQUOTED)
		printf("%s", "UNQUOTED");
	else if (state == WEAK_QUOTE)
		printf("%s", "WEAK_QUOTE");
	else if (state == STRONG_QUOTE)
		printf("%s", "STRONG_QUOTE");
	else if (state == ESCAPE)
		printf("%s", "ESCAPE");
	printf("\n");
}

void	update_state(t_Word_State *state, const char c, const char **delim, bool *term)
{
	// static const char	*delim_unquoted = " \t\n|&;()<>";
	static const char	*delim_strong = "'";
	static const char	*delim_weak = "\"";

	if (c == '"')
	{
		*state = WEAK_QUOTE;
		*delim = delim_weak;
		if (*term == false)
			*term = true;
		else
			*term = false;
	}
	else if (c == '\'')
	{
		*state = STRONG_QUOTE;
		*delim = delim_strong;
		if (*term == false)
			*term = true;
		else
			*term = false;
	}
	else if (c == '\\')
		*state = ESCAPE;
	// else
	// {
	// 	*state = UNQUOTED;
	// 	*delim = delim_unquoted;
	// }
}

bool	is_quoted(t_Word_State state);
/**
* At this point, all operators have been checked for. The remaining token
* can only be a word, where quotes and escapes have to be handled carefully.
*/

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

void	handle_weak_quotes(char **curr, bool *term, t_Word_State *state, const char *delim);

// void	match_word(t_Lexer *lexer, t_Token_list *tokens)
// {
// 	t_Word_State	state = UNQUOTED;
// 	t_Line			*current_line = lexer->line;
// 	char			*curr = current_line->start;
// 	const char		*delimiter = " \t\n|&;()<>";
// 	bool			terminated = true;
//
// 	while (*curr)
// 	{
// 		update_state(&state, *curr, &delimiter, &terminated);
// 		curr++;
// 		if (state == WEAK_QUOTE)
// 		{
// 			handle_weak_quotes(&curr, &terminated, &state, delimiter);
// 			break ;
// 		}
// 		else if (state == STRONG_QUOTE)
// 		{
// 			;
// 		}
// 		else if (is_delimiter(*curr, delimiter))
// 		{
// 			curr++;
// 			break ;
// 		}
// 	}
//
// 	char	*lexeme = ft_substr(lexer->start, 0, curr - (lexer->start + 1));
// 	add_token(tokens, create_token(WORD, lexeme));
// 	lexer->start += ft_strlen(tokens->tail->lexeme);
// }

void	handle_weak_quotes(char **curr, bool *term, t_Word_State *state, const char *delim)
{
	// char	*c = *curr;
	//
	// while (*c && *c != '"')
	// {
	// 	if (*c == '\n' && *term == false)
	// 	{
	// 		write(STDERR_FILENO, "> ", 2);
	// 		printf("not terminated bruh\n");
	// 	}
	// 	c++;	
	// }
	// if (*c == '"')
	// 	update_state(state, **curr, &delim, term);

	while (**curr && **curr != '"')
	{
		if (**curr == '\n' && *term == false)
		{
			write(STDERR_FILENO, "> ", 2);
			printf("not terminated lol\n");
		}
		(*curr)++;
	}
	if (**curr == '"')
		update_state(state, **curr, &delim, term);
}

// void	match_word1(t_Lexer *lexer, t_Token_list *tokens)
// {
// 	t_Word_State	state;
// 	const char		*curr = lexer->start;
// 	const char		*next = curr + 1;
// 	const char		*delimiter;
// 	bool			terminated;
//
// 	state = UNQUOTED;
// 	delimiter = " \t|&;()<>";
// 	terminated = true;
// 	while (*next != '\n' && ft_strchr(delimiter, *next) == NULL)
// 	{
// 		update_state(&state, *curr, &delimiter, &terminated);
// 		check_state(state);
// 		curr++;
// 		next++;
// 	}
// 	update_state(&state, *curr, &delimiter, &terminated);
// 	check_state(state);
// 	while (!terminated && is_quoted(state))
// 	{
// 		printf("not terminated bro\n");
// 		write(STDERR_FILENO, "> ", 2);
// 		const char *next_line = get_next_line(STDIN_FILENO);
// 		char *joined = ft_strjoin(lexer->line, next_line);
// 		size_t old_line_len = ft_strlen(lexer->line);
// 		ptrdiff_t	offset = lexer->start - lexer->line;
// 		*lexer->history = joined;
// 		lexer->line = *lexer->history;
// 		lexer->start = lexer->line + offset;
// 		curr = lexer->start + old_line_len - 1;
// 		next = curr + 1;
// 		while (*next != '\n' && ft_strchr(delimiter, *next) == NULL)
// 		{
// 			update_state(&state, *curr, &delimiter, &terminated);
// 			curr++;
// 			next++;
// 		}
// 		update_state(&state, *curr, &delimiter, &terminated);
// 		check_state(state);
// 	}
// 	add_token(tokens, create_token(WORD,
// 		extract_substring(lexer->start, curr)));
// 	lexer->start += ft_strlen(tokens->tail->lexeme);
// }



bool	is_quoted(t_Word_State state)
{
	return (state == WEAK_QUOTE || state == STRONG_QUOTE);
}


#define DELIMITERS " \t\n|&;()<>"

void	match_word(t_Lexer *lexer, t_Token_list *tokens)
{(void)lexer;(void)tokens;

	char	*c = lexer->line->start;

	printf("Start: %p\n", c);
	while (*c != '\0')
	{
		if (is_delimiter(*c, DELIMITERS))
			break ;
		if (!is_delimiter(*c, DELIMITERS))
		{
			c++;
			continue ;
		}
	}
	printf("End: %p\n", c);
	exit(1);
}
