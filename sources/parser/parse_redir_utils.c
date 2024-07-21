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
