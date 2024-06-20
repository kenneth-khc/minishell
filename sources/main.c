/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 16:18:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "input.h"
#include "tokens.h"
#include "parser.h"

void	free_tokens(t_Token_List *tokens);
char	*get_history(t_Input *input);

int	main(int argc, char **argv, char **envp)
{
	t_Token_List	tokens;
	t_Input			input;
	t_Parser		parser;

	(void)argc;
	(void)argv;
	(void)envp;
	input = (t_Input){0};
	while (1)
	{
		get_input(&input);
		tokens = scan(&input);	
		add_history(get_history(&input));
		print_tokens(&tokens);
		parse(&parser, &tokens);
		clear_input(&input);
		free_tokens(&tokens);
	}
}

char	*get_history(t_Input *input)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = "";
	while (i < input->count)
	{
		buffer = ft_strjoin(buffer, input->lines[i]->start);
		i++;
	}
	return (buffer);
}

void	free_tokens(t_Token_List *tokens)
{
	t_Token	*curr;
	t_Token	*prev;

	curr = tokens->head;
	while (curr != NULL)
	{
		free((void *)curr->lexeme);
		curr->lexeme = NULL;
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

