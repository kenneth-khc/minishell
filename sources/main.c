/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:13:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/16 14:58:27 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include "input.h"
#include "tokens.h"
#include "parser.h"
#include "a.h"
#include <readline/readline.h>
#include "serialize_tree.h"

int	main(int argc, char **argv, char **envp)
{
	t_Token_List	tokens;
	t_Input			input;
	t_Parser		parser;
	t_Node			*root;

	(void)argc;
	(void)argv;
	input = (t_Input){0};

	parser.envtab = init_env_table(envp);
	incr_shlvl(parser.envtab);
	while (1)
	{
		init_signal();
		get_input(&input);
		tokens = scan(&input);
		//print_tokens(&tokens);
		expand_tokens(&tokens, parser.envtab);
		parser.tokens = &tokens;
		parser.token = tokens.head;
		// root = parse(&parser, &tokens);
		root = parse(&parser);
		export_tree(root);
		if (root)
			exec_ast(root);
		clear_input(&input);
		free_tokens(&tokens);
		free_tree(root);
	}
	clear_history();
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

void	free_tree(t_Node *node)
{
	t_Node	*temp;
	t_Exec_Node	*enode;

	temp = node;
	if (node == NULL)
		return ;
	if (node->type == Exec_Node)
	{
		enode = (t_Exec_Node *)node;
		free(enode->args);
	}
	free_tree(node->left);
	free_tree(node->right);
	free(temp);
}

