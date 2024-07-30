/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:16:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 10:11:55 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_Node	*parse(t_Parser *parser)
{
	t_Node	*root;

	root = parse_list(parser);
	if (parser->token)
		expect(parser, END_OF_LINE, "expecting end of line");
	return (root);
}

void	init_parser(t_Parser *parser, t_Token_List *tokens, t_entab *env)
{
	parser->tokens = tokens;
	parser->token = tokens->head;
	parser->envtab = env;
	parser->syntax_ok = true;
}
