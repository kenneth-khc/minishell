/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_matching2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:53:28 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:47:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include "libft.h"

void	match_word1(t_Lexer *scanner, t_Token_list *tokens)
{
	char	*word;

	if (*scanner->lookahead == '\'' || *scanner->lookahead == '"')
		match_quotes(scanner, tokens);
	else
	{
		while (!is_metacharacter(*scanner->lookahead))
			scanner->lookahead++;
		word = ft_substr(scanner->start, 0, scanner->lookahead - scanner->start);
		// word = extract_substring(scanner->start, scanner->lookahead);
		add_token(tokens, create_token(WORD, word));
		scanner->start = scanner->lookahead;
	}
}

void	match_quotes(t_Lexer *scanner, t_Token_list *tokens)
{
	t_Token	*token;
	bool	terminated;

	terminated = is_quote_terminated(scanner);
	if (!terminated)
	{
		prompt_until_terminated(scanner, terminated);
	}
	// while (!is_metacharacter(*scanner->lookahead))
	// 	scanner->lookahead++;
	token = create_token(WORD, NULL);
	token->lexeme = get_quoted_word(scanner);
	// token->lexeme = extract_substring(scanner->start, scanner->lookahead);
	add_token(tokens, token);
	scanner->lookahead++;
	scanner->start = scanner->lookahead;
}

bool	is_quote_terminated(t_Lexer *scanner)
{
	const char	*ptr = scanner->start;
	const char	quote = *ptr;

	while (*ptr != '\0')
	{
		ptr++;
		if (*ptr == quote)
			return (true);
	}
	return (false);
}

#include <stddef.h>
void	prompt_until_terminated(t_Lexer *scanner, bool terminated)
{
	char		*next_line;
	char		*next_lines;
	const char	quote = *scanner->start;
	ptrdiff_t	start_offset;

	next_lines = malloc(1);
	next_lines[0] = '\0';
	while (!terminated)
	{
		write(STDERR_FILENO, "> ", 2);
		next_line = get_next_line(STDIN_FILENO);
		terminated = ft_strchr(next_line, quote);
		next_lines = ft_strjoin(next_lines, next_line);
	}
	start_offset = scanner->start - scanner->line;
	*scanner->history = ft_strjoin(scanner->line, next_lines);
	scanner->line = *scanner->history;
	scanner->start = scanner->line + start_offset;
	scanner->lookahead = scanner->start;
}
#include <stdio.h>
char	*get_quoted_word(t_Lexer *scanner)
{
	const char	quote = *scanner->start;

	scanner->lookahead++;
	while (*scanner->lookahead != quote && *scanner->lookahead !='\0')
		scanner->lookahead++;
	printf("substring: %s\n", extract_substring(scanner->start, scanner->lookahead));
	// return (ft_substr(scanner->start, 0, scanner->lookahead - scanner->start));
	return (extract_substring(scanner->start, scanner->lookahead));
}
