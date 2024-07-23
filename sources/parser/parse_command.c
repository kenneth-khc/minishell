/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:20:58 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 19:23:41 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "tree.h"
#include "parser.h"

t_Node	*make_command_tree(t_Node *prefix, t_Node *cmd, t_Node *suffix);

/**
 * Get the command and its prefixes and suffixes
 * Prefixes are IO_REDIRECTs and ASSIGNMENT_WORDs
 * Command consists of the command name and its arguments
 * Suffixes are WORDs as command arguments and IO_REDIRECTs
 * Redirections and assignments are all processed from left to right
 * before executing the command
 **/
t_Node	*parse_simple_command(t_Parser *parser)
{
	t_Node	*prefix;
	t_Node	*suffix;
	t_Node	*root;
	t_Node	*cmd;

	prefix = parse_command_prefix(parser);
	cmd = parse_command(parser);
	suffix = parse_command_suffix(parser, prefix, (t_Exec_Node *) cmd);
	root = make_command_tree(prefix, cmd, suffix);
	return (root);
}

/**
* Prefixes are IO_REDIRECTs and ASSIGNMENT_WORDs
* They should be executed in order from left to right, so we
* have to add in each new node to the tail of the chain
* e.g. ">one <two a=b" becomes a chain of
* [>one] -> NULL
* [>one] -> [<two] -> NULL
* [>one] -> [<two] -> [a=b] -> NULL
**/
t_Node	*parse_command_prefix(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*node;
	t_Node	**curr;

	root = NULL;
	node = NULL;
	curr = &root;
	while (peek(parser) == ASSIGNMENT_WORD || is_io_redirect(parser))
	{
		if (peek(parser) == ASSIGNMENT_WORD)
			node = assignment_node(parser);
		else if (is_io_redirect(parser))
			node = parse_io_redirect(parser);
		while (*curr != NULL)
			curr = &(*curr)->left;
		*curr = node;
	}
	return (root);
}

/**
 * Parse the command into an execution node
 * The first WORD is the command's name
 * Every WORD after are arguments passed to the command
 **/
t_Node	*parse_command(t_Parser *parser)
{
	t_Exec_Node	*exec;
	bool		cmd_name_set;

	exec = NULL;
	cmd_name_set = false;
	while (accept(parser, WORD))
	{
		if (cmd_name_set == false)
		{
			exec = exec_node(parser->consumed->lexeme, parser->envtab);
			cmd_name_set = true;
		}
		add_exec_arguments(exec, parser->consumed->lexeme);
	}
	return ((t_Node *) exec);
}

/**
 * Construct a chain of all the suffixes of a command.
 * A suffix could be WORD arguments passed to the command, or IO_REDIRECT
 * Since ASSIGNMENT_WORDs can't appear in suffixes, we pretend they are
 * WORDs and treat them as such.
**/
t_Node	*parse_command_suffix(t_Parser *parser, t_Node *prefix,
	t_Exec_Node *exec_node)
{
	t_Node	*root;
	t_Node	**curr;

	root = NULL;
	if (prefix)
		curr = &prefix;
	else
		curr = &root;
	while (peek(parser) == ASSIGNMENT_WORD
		|| peek(parser) == WORD || is_io_redirect(parser))
	{
		if (accept(parser, WORD))
			add_exec_arguments(exec_node, parser->consumed->lexeme);
		else if (accept(parser, ASSIGNMENT_WORD))
			add_exec_arguments(exec_node, parser->consumed->lexeme);
		if (is_io_redirect(parser))
		{
			while (*curr != NULL)
				curr = &(*curr)->left;
			*curr = parse_io_redirect(parser);
		}
	}
	return (root);
}

/**
 * Chain the prefix, command and suffix lists into one.
 * All prefix and suffix happens before the command, so command is placed
 * at the very bottom of the chain
**/
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
