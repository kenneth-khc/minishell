/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_matching2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:53:28 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/15 20:54:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include "libft.h"

void	match_word(t_Lexer *scanner, t_Token_list *tokens)
{
	char	*word;

	if (*scanner->lookahead == '\'' || *scanner->lookahead == '"')
		match_quotes(scanner, tokens);
	else
	{
		while (*scanner->lookahead != ' ' && *scanner->lookahead != '\0')
			scanner->lookahead++;
		word = ft_substr(scanner->start, 0, scanner->lookahead - scanner->start);
		add_token(tokens, create_token(WORD, word));
		scanner->start = scanner->lookahead;
	}
}

bool	is_word_terminated(t_Lexer *scanner)
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

char	*get_quoted_word(t_Lexer *scanner)
{
	const char	quote = *scanner->start;

	scanner->lookahead++;
	while (*scanner->lookahead != quote && *scanner->lookahead != '\0')
		scanner->lookahead++;
	scanner->lookahead++;
	return (ft_substr(scanner->start, 0, scanner->lookahead - scanner->start));
}

#include <stddef.h>
#include <readline/readline.h>
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

void	match_quotes(t_Lexer *scanner, t_Token_list *tokens)
{
	t_Token	*token;
	bool	terminated;

	terminated = is_word_terminated(scanner);
	if (!terminated)
	{
		prompt_until_terminated(scanner, terminated);
	}
	token = create_token(WORD, NULL);
	token->lexeme = get_quoted_word(scanner);
	add_token(tokens, token);
}
