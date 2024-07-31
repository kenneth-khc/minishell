/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:22:35 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 16:38:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "libft.h"
#include "tokens.h"

t_Node	*parse_pipe_sequence(t_Parser *parser)
{
	t_Node	*left;
	t_Node	*pipe;

	left = parse_simple_command(parser);
	while (accept(parser, PIPE))
	{
		pipe = callocpromax(1, sizeof(*pipe));
		pipe->type = PIPE_NODE;
		pipe->left = left;
		if (pipe->left == NULL)
			syntax_error(parser, "expected operand before `|`",
				parser->consumed->prev);
		pipe->right = parse_list(parser);
		if (pipe->right == NULL)
			syntax_error(parser, "expected operand after `|`",
				parser->token);
		left = pipe;
	}
	return (left);
}
