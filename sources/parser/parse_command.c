/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:20:58 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 19:19:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "tokens.h"
#include "tree.h"
#include "parser.h"

t_Node	*make_command_tree(t_Node *prefix, t_Node *cmd, t_Node *suffix);

t_Node	*parse_simple_command(t_Parser *parser)
{
	t_Node	*prefix;
	t_Node	*suffix;
	t_Node	*ret;
	t_Node	*cmd;

	prefix = parse_command_prefix(parser);
	cmd = parse_command_args(parser);
	suffix = parse_command_suffix(parser, prefix, (t_Exec_Node *)cmd);
	ret = make_command_tree(prefix, cmd, suffix);
	return (ret);
}

t_Node	*parse_command_prefix(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	*curr;

	node = NULL;
	curr = NULL;
	root = NULL;
	while (peek(parser) == ASSIGNMENT_WORD || is_io_redirect(parser))
	{
		if (peek(parser) == ASSIGNMENT_WORD)
			node = assignment_node(parser);
		else if (is_io_redirect(parser))
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

t_Node	*make_command_tree(t_Node *prefix, t_Node *cmd, t_Node *suffix)
{
	t_Node	*ret;

	ret = NULL;
	if (prefix)
	{
		ret = prefix;
		if (cmd)
			get_tail(prefix)->left = cmd;
	}
	else if (cmd)
	{
		ret = cmd;
		if (suffix)
		{
			get_tail(suffix)->left = cmd;
			ret = suffix;
		}
	}
	else if (suffix)
		ret = suffix;
	return (ret);
}

t_Node	*parse_command_args(t_Parser *parser)
{
	t_Node		*ret;
	t_Exec_Node	*exec_node;

	exec_node = create_exec_node(NULL, parser->envtab);
	while (peek(parser) == WORD)
	{
		add_exec_arguments(exec_node, parser->token->lexeme);
		consume(parser);
	}
	if (exec_node->command == NULL)
	{
		ret = NULL;
		free(exec_node);
	}
	else
		ret = (t_Node *)exec_node;
	return (ret);
}

t_Node	*parse_command_suffix(t_Parser *parser, t_Node *prefix,
	t_Exec_Node *exec_node)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	*curr;

	root = NULL;
	node = NULL;
	curr = NULL;
	// todo: there shouldn't be assignment words in suffix
	while (peek(parser) == ASSIGNMENT_WORD
		|| peek(parser) == WORD || is_io_redirect(parser))
	{
		if (peek(parser) == ASSIGNMENT_WORD || peek(parser) == WORD)
		{
			if (exec_node == NULL)
				exec_node = create_exec_node(NULL, parser->envtab);
			add_exec_arguments(exec_node, parser->token->lexeme);
			consume(parser);
		}
		if (is_io_redirect(parser))
		{
			node = parse_io_redirect(parser);
			if (prefix)
				get_tail(prefix)->left = node;
			else
			{
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
		}
	}
	return (root);
}
