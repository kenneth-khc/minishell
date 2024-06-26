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

t_Node	*parse_pipe_sequence(t_Parser *parser)
{
	t_Node	*node;

	node = parse_simple_command(parser);

	return (node);
}

