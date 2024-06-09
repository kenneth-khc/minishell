/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/10 02:13:41 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "input.h"

int	main(int argc, char **argv, char **envp)
{
	t_Token_list	tokens;
	t_Input			input;

	(void)argc;
	(void)argv;
	(void)envp;
	input = (t_Input){0};
	while (1)
	{
		get_input(&input);
		tokens = scan(&input);
		add_history(input.lines[0]->start);
		print_tokens(&tokens);
		clear_input(&input);
	}
}

