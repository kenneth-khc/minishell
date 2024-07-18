/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:22:35 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 16:27:02 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "libft.h"
#include "errors.h"
#include "tokens.h"
#include <stdio.h>

t_Node	*parse_pipe_sequence(t_Parser *parser)
{
	t_Node	*left;
	t_Node	*temp;

	left = parse_simple_command(parser);
	while (parser->token->type == PIPE)
	{
		consume(parser);
		temp = ft_calloc(1, sizeof(*temp));
		temp->type = Pipe_Node;
		temp->left = left;
		temp->right = parse_list(parser);
		if (temp->right == NULL)
		{
			syntax_error(parser, "missing command to pipe to\n");
			return (NULL);
		}
		left = temp;
	}
	return (left);
}
