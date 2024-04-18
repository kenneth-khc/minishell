/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 18:00:21 by kecheong         ###   ########.fr       */
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
		line = get_line();
		tokens = scan(&line);
		add_history(line);
		print_tokens(&tokens);
		free(line);
	}
}

char	*get_line(void)
{
	char	*line;
	char	*append;

	line = readline("bish> ");
	if (line == NULL)
		printf("handle eof!\n"), exit(EXIT_FAILURE);
	append = ft_strjoin(line, "\n");
	free(line);
	return (append);
}
