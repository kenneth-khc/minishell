/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:34:40 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 17:01:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_Node	*parse_subshell(t_Parser *parser)
{
	t_Node	*subshell;

	if (!accept(parser, OPEN_PARAN))
		syntax_error(parser, "expected opening parenthesis", parser->token);
	subshell = node(SUBSHELL_NODE);
	subshell->left = parse_list(parser);
	if (subshell->left == NULL)
		syntax_error(parser, "expected list in subshell",
			parser->consumed->prev);
	if (expect(parser, CLOSE_PARAN, "expected closing parenthesis"))
		consume(parser);
	return (subshell);
}
