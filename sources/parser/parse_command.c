/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:20:58 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/06 19:20:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "parser.h"
#include <stdio.h>
#include "debug.h"

bool	is_and_or_token(t_Token *token)
{
	return (token->type == AND_AND
			|| token->type == OR_OR);
}

t_Node	*parse_complete_command(t_Parser *parser)
{
	t_Node	*node;
	t_Node	*andor;

	node = parse_pipe_sequence(parser);
	while (is_and_or_token(parser->token))
	{
		andor = ft_calloc(1, sizeof(*andor));
		if (peek_token(parser->token) == AND_AND)
			andor->type = AND_AND_NODE;
		else if (peek_token(parser->token) == OR_OR)
			andor->type = OR_OR_NODE;
		consume(parser);
		andor->left = node;
		andor->right = parse_pipe_sequence(parser);
		node = andor;
	}
	return (node);
}

t_Node	*parse_simple_command(t_Parser *parser)
{
	t_Node		*prefix;
	t_Node		*suffix;
	t_Node		*ret;
	t_Exec_Node	*exec_node;

	exec_node = create_exec_node(NULL, parser->envtab);
	prefix = parse_command_prefix(parser);
	while (peek_token(parser->token) == WORD)
	{
		add_exec_arguments(exec_node, parser->token->lexeme);
		consume(parser);
	}
	suffix = parse_command_suffix(parser, exec_node);
	if (prefix)
	{
		ret = prefix;
		if (suffix)
		{
			get_tail(prefix)->left = suffix;
			get_tail(suffix)->left = (t_Node *)exec_node;
		}
		else
		{
			get_tail(prefix)->left = (t_Node *)exec_node;
		}
	}
	else if (suffix)
	{
		ret = suffix;
		get_tail(suffix)->left = (t_Node *)exec_node;
	}
	else
		ret = (t_Node *)exec_node;
	if (exec_node->command == NULL)
	{
		ret = NULL;
		free(exec_node);
	}
	return (ret); // todo: add more expressions
}

t_Node	*parse_command_prefix(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	*curr;

	node = NULL;
	curr = NULL;
	root = NULL;
	while (is_redirection_token(parser->token))
	{
		node = parse_io_redirect(parser);
		if (root == NULL)
		{
			root = node;
			curr = root;
		}
		else
		{
			curr->left = node;
			curr = node;
		}
	}
	return (root);
}

t_Node	*parse_command_suffix(t_Parser *parser, t_Exec_Node *exec_node)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	*curr;

	root = NULL;
	node = NULL;
	curr = NULL;
	while (is_redirection_token(parser->token))
	{
		node = parse_io_redirect(parser);
		if (root == NULL)
		{
			root = node;
			curr = root;
		}
		else
		{
			curr->left = node;
			curr = node;
		}
	}
	while (peek_token(parser->token) == WORD)
	{
		add_exec_arguments(exec_node, parser->token->lexeme);
		consume(parser);
	}
	return (root);
}

// TODO: fix
t_Exec_Node	*parse_command_name(t_Parser *parser)
{
	t_Exec_Node	*exec_node;

	exec_node = NULL;
	if (peek_token(parser->token) == WORD)
	{
		exec_node = create_exec_node(parser->token->lexeme, parser->envtab);
		consume(parser);
		while (parse_command_suffix(parser, exec_node))
			;
	}
	// parser->root = (t_Node *)exec_node; // temp
	return (exec_node);
}

// TODO: fix
bool	parse_command_word(t_Parser *parser)
{ (void)parser;return(PARSE_FAIL);
	;
}

