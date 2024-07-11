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

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "tree.h"
#include "tokens.h"
#include "debug.h"
#include "errors.h"

#define BLUE "\e[0;34m\0"

t_Node	*parse_command(t_Parser *parser)
{
	t_Node	*root;

	if (accept(parser, OPEN_PARAN))
	{
		root = parse_subshell(parser);
	}
	else
	{
		root = parse_list(parser);
	}
	return (root);
}

t_Node	*parse_subshell(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*node;

	root = ft_calloc(1, sizeof(*node));
	root->type = SUBSHELL_NODE;
	root->left = parse_list(parser);
	if (!expect(parser, CLOSE_PARAN))
	{
		syntax_error(parser, "expected closing parenthesis");
		return (NULL);
	}
	while (peek(1, parser) == PIPE
			|| is_and_or(parser))
	{
		node = ft_calloc(1, sizeof(*node));
		if (accept(parser, PIPE))
			node->type = Pipe_Node;
		else if (accept(parser, AND_AND))
			node->type = AND_AND_NODE;
		else if (accept(parser, OR_OR))
			node->type = OR_OR_NODE;
		node->left = root;
		node->right = parse_command(parser);
		root = node;
	}
	return (root);
}

t_Node	*parse_list(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*and_or;

	root = parse_pipe_sequence(parser);
	while (is_and_or(parser))
	{
		and_or = ft_calloc(1, sizeof(*and_or));
		if (peek(1, parser) == AND_AND)
			and_or->type = AND_AND_NODE;
		else if (peek(1, parser) == OR_OR)
			and_or->type = OR_OR_NODE;
		consume(parser);
		and_or->left = root;
		and_or->right = parse_pipe_sequence(parser);
		root = and_or;
	}
	return (root);
}

