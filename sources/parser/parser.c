/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:16:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 17:09:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "tree.h"
#include "tokens.h"
#include "libft.h"
#include "errors.h"

t_Node	*parse(t_Parser *parser)
{
	t_Node	*root;

	root = parse_list(parser);
	return (root);
}

t_Node	*parse_list(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*and_or;

	if (peek(parser) == OPEN_PARAN)
		root = parse_subshell(parser);
	else
		root = parse_pipe_sequence(parser);
	while (is_and_or(parser))
	{
		and_or = ft_calloc(1, sizeof(*and_or));
		if (peek(parser) == AND_AND)
			and_or->type = AND_AND_NODE;
		else if (peek(parser) == OR_OR)
			and_or->type = OR_OR_NODE;
		consume(parser);
		and_or->left = root;
		if (peek(parser) == OPEN_PARAN)
			and_or->right = parse_subshell(parser);
		else
			and_or->right = parse_pipe_sequence(parser);
		root = and_or;
	}
	return (root);
}

t_Node	*parse_subshell(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*node;

	accept(parser, OPEN_PARAN);
	root = ft_calloc(1, sizeof(*node));
	root->type = SUBSHELL_NODE;
	root->left = parse_list(parser);
	if (root->left == NULL)
		syntax_error(parser, "expected list in subshell");
	if (expect(parser, CLOSE_PARAN, "expected closing parenthesis"))
		consume(parser);
	return (root);
}
