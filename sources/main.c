/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/11 11:54:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "debug.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;(void)argv;(void)envp;
	char	*line;
	t_Token_list	tokens;

	while (1)
	{
		line = readline("bish> ");
		if (line == NULL)
			printf("handle eof!\n"), exit(EXIT_FAILURE);
		tokens = scan(line);
		print_tokens(&tokens);
		printf("%s\n", line);
		free(line);
	}
}