/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:57:43 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/14 12:58:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "ft_dprintf.h"

void	error(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	syntax_error(t_Parser *parser, const char *err_msg)
{
	(void)parser;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", "bish", err_msg);
	free_tree(parser->root);
	parser->root = NULL;
	return ;
}
