/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 19:19:37 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "input.h"
#include "tokens.h"
#include "parser.h"
#include "execution.h"
#include "lexer.h"
#include "expansions.h"
//#include "serialize_tree.h"

const char	*__asan_default_options(void)
{
	return ("detect_leaks=0");
}

void	clean_up(t_Input *input, t_Token_List *tokens, t_Node *tree);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;(void)argv;(void)envp;
	t_Token_List	tokens;
	t_Input			input;
	t_Parser		parser;
	t_Node			*root;
	t_entab			*env;

	(void)argc;
	(void)argv;
	input = (t_Input){0};
	env = init_env_table(envp);
	incr_shlvl(env);
	while (1)
	{
		init_signal();
		get_input(&input);
		tokens = scan(&input);
		expand_tokens(&tokens, env);
		init_parser(&parser, &tokens, env);
		root = parse(&parser);
//		export_tree(root);
		if (root && parser.syntax_ok)
			exec_ast(root);
		clean_up(&input, &tokens, root);
	}
	//clear_history();
}

void	init_parser(t_Parser *parser, t_Token_List *tokens, t_entab *env)
{
	parser->tokens = tokens;
	parser->token = tokens->head;
	parser->envtab = env;
	parser->syntax_ok = true;
}

void	clean_up(t_Input *input, t_Token_List *tokens, t_Node *tree)
{
	clear_input(input);
	free_tokens(tokens);
	free_tree(tree);
}
