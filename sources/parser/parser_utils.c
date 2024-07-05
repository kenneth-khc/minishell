/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:47:44 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/26 23:49:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdbool.h>
#include <stdio.h>

// Checks if a token is for redirection
bool	is_redirection_token(t_Token *token)
{
	if (token)
	{
		return (token->type == LESSER ||
			token->type == LESSER_LESSER ||
			token->type == GREATER ||
			token->type == GREATER_GREATER);
	}
	return (false);
}

enum e_Token_Types	peek_token(t_Token *token)
{
	if (token == NULL)
		return 0;
	return (token->type);
}

