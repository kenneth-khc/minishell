/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:22:35 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/26 22:25:08 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <unistd.h>
#include "errors.h"

t_Node	*parse_pipe_sequence(t_Parser *parser)
{
	t_Node	*left;
	t_Node	*temp;

	left = parse_simple_command(parser);
	while (peek_token(parser->token) == PIPE)
	{
		consume(parser);
		temp = ft_calloc(1, sizeof(*temp));
		temp->type = Pipe_Node;
		temp->left = left;
		temp->right = parse_simple_command(parser);
		if (temp->right == NULL)
		{
			syntax_error(parser, "missing command to pipe to\n");
			return (NULL);
		}
		left = temp;
	}
	return (left);
}

