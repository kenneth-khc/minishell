/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:14:17 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 18:22:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parser.h"
#include "tokens.h"

/**
 * Checks if a token is a redirection operator
 **/
bool	is_redirection_token(t_Token *token)
{
	if (token)
	{
		return (token->type == LESSER
			|| token->type == LESSER_LESSER
			|| token->type == GREATER
			|| token->type == GREATER_GREATER);
	}
	return (false);
}

/**
 * Checks if a token is a redirection operator or
 * a fd in front of the operator
**/
bool	is_io_redirect(t_Parser *parser)
{
	return (peek(parser) == IO_NUMBER
		|| is_redirection_token(parser->token));
}

/**
* HACK: we flag the last heredoc and only dup that heredoc
* into the file descriptor for the command 
**/
void	flag_last_heredoc(t_Node *root)
{
	t_Node			*curr;
	t_Redir_Node	*last_heredoc_node;
	t_Redir_Node	*r;

	curr = root;
	last_heredoc_node = NULL;
	while (curr)
	{
		if (curr->type == Redir_Node)
		{
			r = (t_Redir_Node *) curr;
			if (r->heredoc)
				last_heredoc_node = r;
		}
		curr = curr->left;
	}
	if (last_heredoc_node)
		last_heredoc_node->last_heredoc = true;
}
