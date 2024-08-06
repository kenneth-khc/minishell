/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 05:38:49 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "ft_dprintf.h"
#include "input.h"
#include "tokens.h"
#include "parser.h"
#include "execution.h"
#include "lexer.h"
#include "expansions.h"

static void
interactive(t_entab *env);

static void
interpret(char *input_line, t_entab *env);

int	main(int argc, char **argv, char **envp)
{
	t_entab	*env;

	env = init_env_table(envp);
	if (argc == 1)
	{
		interactive(env);
	}
	else if (argc == 2)
	{
		interpret(argv[1], env);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Usage:\n");
		ft_dprintf(STDERR_FILENO, "Interactive mode > ./minishell\n");
		ft_dprintf(STDERR_FILENO, "Interpret a line > ./minishell <line>\n");
		return (EXIT_FAILURE);
	}
	free_env(env);
	return (EXIT_SUCCESS);
}

static void	interactive(t_entab *env)
{
	t_Token_List	tokens;
	t_Input			input;
	t_Parser		parser;
	t_Node			*root;

	input = (t_Input){.line_count = 0, .lines = NULL, .ok = true};
	incr_shlvl(env);
	while (1)
	{
		init_signal();
		get_input(&input);
		tokens = scan(&input);
		if (input.ok)
		{
			add_input_to_history(&input);
			expand_tokens(&tokens, env);
			init_parser(&parser, &tokens, env);
			root = parse(&parser);
			if (root && parser.syntax_ok)
				exec_ast(root);
			free_tree(root);
		}
		clear_input(&input);
		free_tokens(&tokens);
	}
}

static void	interpret(char *input_line, t_entab *env)
{
	t_Input			input;
	t_Token_List	tokens;
	t_Node			*root;
	t_Parser		parser;
	t_String		*newline;

	input = (t_Input){.line_count = 0, .lines = NULL, .ok = true};
	newline = string_join(stringify(input_line), stringify("\n"));
	store_input(&input, newline);
	incr_shlvl(env);
	tokens = scan(&input);
	expand_tokens(&tokens, env);
	init_parser(&parser, &tokens, env);
	root = parse(&parser);
	if (root && parser.syntax_ok)
		exec_ast(root);
	clear_input(&input);
	free_tree(root);
	free_tokens(&tokens);
}

const char	*__asan_default_options(void)
{
	return ("detect_leaks=1");
}
