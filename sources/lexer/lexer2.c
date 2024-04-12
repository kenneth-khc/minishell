/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:32:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/12 10:59:54 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include <stdio.h>

void	scan_bar(const char **ptr_to_line, t_Token_list *tokens)
{
	const char	*line;
	char		lookahead;

	line = *ptr_to_line;
	lookahead = *(line + 1);
	if (lookahead == '|')
	{
		add_token(tokens, create_token(OR_OR, NULL));
		(*ptr_to_line)++;
	}
	else
	{
		add_token(tokens, create_token(PIPE, NULL));
	}
}

void	scan_lesser(const char **ptr_to_line, t_Token_list *tokens)
{
	const char	*line;
	char		lookahead;

	line = *ptr_to_line;
	lookahead = *(line + 1);
	if (lookahead == '<')
	{
		add_token(tokens, create_token(LESSER_LESSER, NULL));
		(*ptr_to_line)++;
	}
	else
	{
		add_token(tokens, create_token(LESSER, NULL));
	}
}

void	scan_greater(const char **ptr_to_line, t_Token_list *tokens)
{
	const char	*line;
	char		lookahead;

	line = *ptr_to_line;
	lookahead = *(line + 1);
	if (lookahead == '>')
	{
		add_token(tokens, create_token(GREATER_GREATER, NULL));
		(*ptr_to_line)++;
	}
	else
	{
		add_token(tokens, create_token(GREATER, NULL));
	}
}

# include "lexer.h"
void	scan_word(const char **ptr_to_line, t_Token_list *tokens)
{
	const char	*line = *ptr_to_line;
	const char	*lookahead = line;

	if (*lookahead == '\'' || *lookahead == '"')
	{
		scan_quotes(ptr_to_line, tokens);
	}
	else
	{
		while (*lookahead != ' ' && *lookahead != '\0')
			lookahead++;
		int	consumed;
		consumed = lookahead - line;
		add_token(tokens, create_token(WORD, ft_substr(line, 0, consumed)));
		*ptr_to_line += consumed;
	}
}
# include <readline/readline.h>

void	scan_quotes(const char **ptr_to_line, t_Token_list *tokens)
{
	const char	*line = *ptr_to_line;
	const char	*lookahead = line;
	const char	quote = *line;
	bool		terminated = false;
	int consumed = 0;

	while (*lookahead != '\0')
	{
		lookahead++;
		consumed++;
		if (*lookahead == quote)
		{
			terminated = true;
			lookahead++;
			consumed++;
			break ;
		}
	}
	while (!terminated)
	{
		char *newline = readline("> ");
		*ptr_to_line = ft_strjoin(*ptr_to_line, newline);
		while (*newline != '\0')
		{
			if (*newline == quote)
				terminated = true;
			newline++;
			consumed++;
		}
	}
	add_token(tokens, create_token(WORD, ft_substr(*ptr_to_line, 0, consumed)));
	*ptr_to_line += consumed-1;
}
