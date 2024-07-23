/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:23:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 16:58:37 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "tokens.h"

static t_Node	*list(t_Parser *parser);
static bool		is_and_or_token(t_Parser *parser);
static void		check_list_left(t_Parser *parser, t_Node *and_or);
static void		check_list_right(t_Parser *parser, t_Node *and_or);

t_Node	*parse_list(t_Parser *parser)
{
	t_Node	*root;
	t_Node	*and_or;

	root = list(parser);
	while (is_and_or_token(parser))
	{
		if (accept(parser, AND_AND))
			and_or = node(AND_AND_NODE);
		else if (accept(parser, OR_OR))
			and_or = node(OR_OR_NODE);
		and_or->left = root;
		check_list_left(parser, and_or);
		and_or->right = list(parser);
		check_list_right(parser, and_or);
		root = and_or;
	}
	return (root);
}

static t_Node	*list(t_Parser *parser)
{
	if (peek(parser) == OPEN_PARAN)
		return (parse_subshell(parser));
	else
		return (parse_pipe_sequence(parser));
}

static bool	is_and_or_token(t_Parser *parser)
{
	return (peek(parser) == AND_AND
		|| peek(parser) == OR_OR);
}

static void	check_list_left(t_Parser *parser, t_Node *and_or)
{
	if (and_or->left == NULL)
	{
		if (and_or->type == AND_AND_NODE)
			syntax_error(parser, "expected operand before `&&`",
				parser->consumed->prev);
		else if (and_or->type == OR_OR_NODE)
			syntax_error(parser, "expected operand before `||`",
				parser->consumed->prev);
	}
}

static void	check_list_right(t_Parser *parser, t_Node *and_or)
{
	if (and_or->right == NULL)
	{
		if (and_or->type == AND_AND_NODE)
			syntax_error(parser, "expected operand after `&&`",
				parser->token);
		else if (and_or->type == OR_OR_NODE)
			syntax_error(parser, "expected operand after `||`",
				parser->token);
	}
}
