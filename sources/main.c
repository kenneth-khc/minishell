/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/17 18:00:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_Token_list	tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("bish> ");
		// free
		line = ft_strjoin(line, "\n");
		if (line == NULL)
			printf("handle eof!\n"), exit(EXIT_FAILURE);
		tokens = scan(&line);
		add_history(line);
		print_tokens(&tokens);
		free(line);
	}
}

t_Token_list	scan(char **line)
{
	t_Token_list	tokens;
	t_Lexer			scanner;

	tokens = (t_Token_list){.head = NULL, .tail = NULL};
	scanner.line = *line;
	scanner.start = *line;
	scanner.lookahead = *line;
	scanner.history = &scanner.line;
	t_Matcher *matchers = init_matchers();
	while (!end_of_line(tokens.tail))
	{
		skip_whitespaces(&scanner);
		match(&scanner, matchers, &tokens);
	}
	return (tokens);
}

void	match(t_Lexer *scanner, t_Matcher *matchers, t_Token_list *tokens)
{
	int	i;

	i = 0;
	while (i < TOKEN_MATCHERS)
	{
		if (*scanner->start == matchers[i].start)
		{
			matchers[i].match_function(scanner, tokens);
		}
		i++;
		if (i == TOKEN_MATCHERS - 1)
			match_word(scanner, tokens);
	}
}

bool	end_of_line(t_Token *token)
{
	return (token && token->type == END_OF_LINE);
}

void	skip_whitespaces(t_Lexer *scanner)
{
	while (*scanner->lookahead == ' '
		|| *scanner->lookahead == '\n'
		|| *scanner->lookahead == '\t')
		scanner->lookahead++;
	scanner->start = scanner->lookahead;
}

