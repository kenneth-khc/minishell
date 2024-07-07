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

#define BLUE "\e[0;34m\0"

t_Node	*parse(t_Parser *parser, t_Token_List *tokens)
{
	t_Node	*root;

	parser->tokens = tokens;
	parser->token = tokens->head;
	parser->root = NULL;

	root = parse_complete_command(parser);
	parser->root = root;
	return (root);
}

t_Node	*parse_complete_command(t_Parser *parser)
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

