/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:29:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/26 22:52:32 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include "debug.h"
#include "libft.h"
#include "tokens.h"

t_Node	*parse_io_redirect(t_Parser *parser)
{
	t_Node	*node;

	node = parse_io_file(parser);
	if (node)
		return (node);
	node = parse_io_here(parser);
	if (node)
		return (node);
	if (node == NULL)
		cerr("expected redirection");
	return (NULL);
}

t_Node	*parse_io_file(t_Parser *parser)
{
	t_Redir_Node	*node;

	node = NULL;
	if (peek(1, parser) == LESSER)
	{
		node = input_redir(parser, O_RDONLY);
	}
	else if (peek(1, parser) == GREATER)
	{
		node = output_redir(parser, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (peek(1, parser) == GREATER_GREATER)
	{
		node = output_redir(parser, O_WRONLY | O_CREAT | O_APPEND);
	}
	return ((t_Node *)node);
}

t_Redir_Node	*input_redir(t_Parser *parser, int flags)
{
	t_Redir_Node	*node;

	if (peek(1, parser), WORD)
	{
		consume(parser);
		node = create_redir_node(STDIN_FILENO, parser->token->lexeme,
				flags, 0666);
		consume(parser);
	}
	else
		node = NULL;
	return (node);
}

t_Redir_Node	*output_redir(t_Parser *parser, int flags)
{
	t_Redir_Node	*node;

	if (peek(2, parser), WORD)
	{
		consume(parser);
		node = create_redir_node(STDOUT_FILENO, parser->token->lexeme,
				flags, 0666);
		consume(parser);
	}
	else
		node = NULL;
	return (node);
}

t_Node	*parse_io_here(t_Parser *parser)
{
	t_Redir_Node	*node;

	node = ft_calloc(1, sizeof(*node));
	if (peek(1, parser) == LESSER_LESSER)
	{
		consume(parser);
		// search for here_end
		if (expect(parser, WORD))
		{
			consume(parser);
			node = create_redir_node(STDIN_FILENO, ".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
			return ((t_Node *)node);
		}
		else
		{
			cerr("missing heredoc end");
			return (NULL);
		}
	}
	else
	{
		cerr("not heredoc");
		return (NULL);
	}
}

