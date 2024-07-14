/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:20:58 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/10 18:16:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "tree.h"
#include "parser.h"
#include <stdio.h>
#include "debug.h"
#include <stdlib.h>

t_Node	*parse_command_args(t_Parser *parser)
{
	t_Node		*ret;
	t_Exec_Node	*exec_node;

	exec_node = create_exec_node(NULL, parser->envtab);
	while (peek(1, parser) == WORD)
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

t_Node	*parse_simple_command(t_Parser *parser)
{
	t_Node	*prefix;
	t_Node	*suffix;
	t_Node	*ret;
	t_Node	*cmd;

	ret = NULL;
	prefix = parse_command_prefix(parser);
	cmd = parse_command_args(parser);
	suffix = parse_command_suffix(parser, prefix, (t_Exec_Node *)cmd);
//	if (prefix) printf("yeh prefix\n");
//	else printf("no prefix\n");
//	if (cmd) printf("yeh cmd\n");
//	else printf("no cmd\n");
//	if (suffix) printf("yeh suffix\n");
//	else printf("no suffix\n");
	if (prefix)
	{
		ret = prefix;
		if (cmd)
		{
			get_tail(prefix)->left = cmd;
			/*
			if (suffix)
			{
				// infinite loop here
				get_tail(suffix)->left = cmd;
				get_tail(prefix)->left = suffix;
			}
			*/
		}
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
	{
		ret = suffix;
	}
	/*
	if (exec_node->command == NULL)
	{
		ret = NULL;
		free(exec_node);
	}
	*/
	return (ret); // todo: add more expressions
}

t_Node	*assignment_node(t_Parser *parser)
{
	t_Ass_Node	*ass;
	const char	*equal;
	const char	*end;

	ass = ft_calloc(1, sizeof(*ass));
	equal = ft_strchr(parser->token->lexeme, '=');
	ass->type = ASS_NODE;
	ass->key = ft_extract_substring(parser->token->lexeme, equal - 1);
	end = parser->token->lexeme + ft_strlen(parser->token->lexeme) - 1;
	ass->value = ft_extract_substring(equal + 1, end);
	ass->left = NULL;
	return ((t_Node *)ass);
}

bool	is_io_redirect(t_Parser *parser)
{
	return (peek(1, parser) == IO_NUMBER || is_redirection_token(parser->token));
}

#include "errors.h"
t_Node	*parse_command_prefix(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	*curr;

	node = NULL;
	curr = NULL;
	root = NULL;
	while (peek(1, parser) == ASSIGNMENT_WORD || is_io_redirect(parser))
	{
		if (peek(1, parser) == ASSIGNMENT_WORD)
		{
			node = assignment_node(parser);
			consume(parser);
		}
		else if (is_io_redirect(parser))
		{
			node = parse_io_redirect(parser);
		}
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

t_Node	*parse_command_suffix(t_Parser *parser, t_Node *prefix, t_Exec_Node *exec_node)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	*curr;

	root = NULL;
	node = NULL;
	curr = NULL;
	// todo: there shouldn't be assignment words in suffix
	while (peek(1, parser) == ASSIGNMENT_WORD ||
		peek(1, parser) == WORD || is_io_redirect(parser))
	{
		// bandaid fix for now
		if (peek(1, parser) == ASSIGNMENT_WORD)
			parser->token->type = WORD;
		//
		if (peek(1, parser) == WORD)
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

