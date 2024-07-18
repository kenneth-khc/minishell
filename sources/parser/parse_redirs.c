/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:29:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 16:56:29 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "tokens.h"

t_Node	*parse_io_redirect(t_Parser *parser)
{
	t_Redir_Node	*node;
	bool			oldfd_set;

	oldfd_set = false;
	node = ft_calloc(1, sizeof(*node));
	node->type = Redir_Node;
	node->table = parser->envtab;
	if (accept(parser, IO_NUMBER))
	{
		node->oldfd = ft_atoi(parser->token->lexeme);
		oldfd_set = true;
	}
	if (accept(parser, LESSER_LESSER))
		heredoc_redir(parser, node, oldfd_set);
	if (accept(parser, LESSER))
		input_redir(parser, node, oldfd_set);
	else if (accept(parser, GREATER))
		trunc_output_redir(parser, node, oldfd_set);
	else if (accept(parser, GREATER_GREATER))
		append_output_redir(parser, node, oldfd_set);
	return ((t_Node *)node);
}

void	trunc_output_redir(t_Parser *parser, t_Redir_Node *node, bool oldfd_set)
{
	if (oldfd_set == false)
		node->oldfd = STDOUT_FILENO;
	node->direction = OUTPUT;
	node->file = parser->token->lexeme;
	node->flags = O_WRONLY | O_CREAT | O_TRUNC;
	node->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	consume(parser);
}

void	append_output_redir(t_Parser *parser, t_Redir_Node *node,
	bool oldfd_set)
{
	if (oldfd_set == false)
		node->oldfd = STDOUT_FILENO;
	node->direction = OUTPUT;
	node->flags = O_WRONLY | O_CREAT | O_APPEND;
	node->file = parser->token->lexeme;
	node->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	consume(parser);
}

void	input_redir(t_Parser *parser, t_Redir_Node *node, bool oldfd_set)
{
	if (oldfd_set == false)
		node->oldfd = STDIN_FILENO;
	node->direction = INPUT;
	node->flags = O_RDONLY;
	node->file = parser->token->lexeme;
	node->mode = 0;
	consume(parser);
}

void	heredoc_redir(t_Parser *parser, t_Redir_Node *node, bool oldfd_set)
{
	if (oldfd_set == false)
		node->oldfd = STDIN_FILENO;
	node->direction = INPUT;
	node->file = NULL;
	node->flags = O_WRONLY | O_CREAT | O_TRUNC;
	node->mode = 0644;
	node->heredoc = true;
	node->delim = parser->token->lexeme;
	consume(parser);
}
