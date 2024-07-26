/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:29:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 18:20:28 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "parser.h"

static void
trunc_output_redir(t_Parser *parser, t_Redir_Node *redir, bool oldfd_set);

static void
append_output_redir(t_Parser *parser, t_Redir_Node *redir, bool oldfd_set);

static void
input_redir(t_Parser *parser, t_Redir_Node *redir, bool oldfd_set);

static void
heredoc_redir(t_Parser *parser, t_Redir_Node *redir, bool oldfd_set);

t_Node	*parse_io_redirect(t_Parser *parser)
{
	t_Redir_Node	*redir;
	bool			oldfd_set;

	oldfd_set = false;
	redir = redir_node(parser->envtab);
	if (peek(parser) == IO_NUMBER)
	{
		redir->oldfd = ft_atoi(parser->token->lexeme);
		oldfd_set = true;
		consume(parser);
	}
	if (accept(parser, LESSER_LESSER))
		heredoc_redir(parser, redir, oldfd_set);
	else if (accept(parser, LESSER))
		input_redir(parser, redir, oldfd_set);
	else if (accept(parser, GREATER))
		trunc_output_redir(parser, redir, oldfd_set);
	else if (accept(parser, GREATER_GREATER))
		append_output_redir(parser, redir, oldfd_set);
	return ((t_Node *)redir);
}

static void	trunc_output_redir(t_Parser *parser, t_Redir_Node *redir,
			bool oldfd_set)
{
	if (oldfd_set == false)
		redir->oldfd = STDOUT_FILENO;
	redir->direction = OUTPUT;
	redir->flags = O_WRONLY | O_CREAT | O_TRUNC;
	redir->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (expect(parser, WORD, "expected filename for output redirection"))
	{
		redir->file = parser->token->lexeme;
		consume(parser);
	}
}

static void	append_output_redir(t_Parser *parser, t_Redir_Node *redir,
			bool oldfd_set)
{
	if (oldfd_set == false)
		redir->oldfd = STDOUT_FILENO;
	redir->direction = OUTPUT;
	redir->flags = O_WRONLY | O_CREAT | O_APPEND;
	redir->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (expect(parser, WORD, "expected filename for output redirection"))
	{
		redir->file = parser->token->lexeme;
		consume(parser);
	}
}

static void	input_redir(t_Parser *parser, t_Redir_Node *redir, bool oldfd_set)
{
	if (oldfd_set == false)
		redir->oldfd = STDIN_FILENO;
	redir->direction = INPUT;
	redir->flags = O_RDONLY;
	redir->mode = 0;
	if (expect(parser, WORD, "expected filename for input redirection"))
	{
		redir->file = parser->token->lexeme;
		consume(parser);
	}
}

static void	heredoc_redir(t_Parser *parser, t_Redir_Node *redir, bool oldfd_set)
{
	if (oldfd_set == false)
		redir->oldfd = STDIN_FILENO;
	redir->direction = INPUT;
	redir->file = NULL;
	redir->flags = O_WRONLY | O_CREAT | O_TRUNC;
	redir->mode = 0644;
	redir->heredoc = true;
	if (expect(parser, WORD, "expected delimiter word for heredoc"))
	{
		redir->delim = ft_strjoin(parser->token->lexeme, "\n");
		consume(parser);
	}
}
