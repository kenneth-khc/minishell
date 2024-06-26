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
#include "ast.h"
#include "tokens.h"
#include <stdlib.h>
#include "debug.h"
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	times_expected = 0;
int times_consumed = 0;

t_Node	*parse(t_Parser *parser, t_Token_List *tokens)
{(void)parser;(void)tokens;
	cout("start parser");
	t_Node	*root;

	parser->token = tokens->head;
	parser->lookahead = parser->token->next;

	root = parse_complete_command(parser);

	// cout("Root: %s", parser->root->value);
	cout("end parser");
	print_nodes(root);
	cout("times expected: %d", times_expected);
	cout("times consumed: %d", times_consumed);
	exit(EXIT_SUCCESS);
	return (root);
}

void	print_nodes(t_Node *node)
{
	t_Redir_Node	*redir;
	t_Exec_Node		*exec;

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
		else
		{
			cerr("Missing node type");
		}
		node = node->left;
	}
}

bool	expect(t_Token *token, enum e_Token_Types expected_type)
{
	times_expected++;
	if (token->type == expected_type)
	{
		cout("Expected %s", token_enum_to_str(token));
		return (PARSE_SUCCESS);
	}
	else
	{
		cout("Unexpected %s", token_enum_to_str(token));
		return (PARSE_FAIL);
	}
}

void	consume(t_Parser *parser)
{
	if (parser->token)
	{
		times_consumed++;
		cout("Consumed %s", token_enum_to_str(parser->token));
		parser->token = parser->token->next;
		if (parser->token)
		parser->lookahead = parser->token->next;
	}
}

