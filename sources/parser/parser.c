/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:16:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/26 22:31:49 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tree.h"
#include "tokens.h"
#include "debug.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
//#include "tree_visualization.h"

#define BLUE "\e[0;34m\0"

t_Node	*parse(t_Parser *parser, t_Token_List *tokens)
{
	t_Node	*root;

	parser->token = tokens->head;
	parser->lookahead = parser->token->next;
	parser->root = NULL;

	root = parse_complete_command(parser);
	parser->root = root;
//	export_tree(root);

	// cout("Root: %s", parser->root->value);
	// cout("end parser");
	// print_nodes(root);
	// exit(EXIT_SUCCESS);
	return (root);
}

void	print_nodes(t_Node *node)
{
	t_Redir_Node	*redir;
	t_Exec_Node		*exec;
	t_Pipe_Node		*pipe;

	while (node)
	{
		if (node->type == Redir_Node)
		{
			redir = (t_Redir_Node *)node;
			cerr("Oldfd: %d\n", redir->oldfd);
			cerr("%s\n", redir->file);
		}
		else if (node->type == Exec_Node)
		{
			exec = (t_Exec_Node *)node;
			if (exec->command)
			{
				cerr("Cmd: %s\n", exec->command);
				cerr("Args: ");
				for (int i=0; i < exec->arg_count; i++)
					cerr("%s ", exec->args[i]);
			}
		}
		else if (node->type == Pipe_Node)
		{
			pipe = (t_Pipe_Node *)node;
			cerr("Piping\n");
			print_nodes(pipe->left);
			print_nodes(pipe->right);
			break ;
		}
		else
		{
			cerr("Missing node type");
		}
		node = node->left;
	}
}

