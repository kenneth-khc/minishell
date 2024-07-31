/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:43:38 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:23:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "libft.h"

t_Token	*create_token(int type, const char *lexeme)
{
	t_Token	*new_token;

	new_token = callocpromax(1, sizeof(*new_token));
	new_token->type = type;
	new_token->lexeme = (char *)lexeme;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_token(t_Token_List *tokens, t_Token *token)
{
	t_Token	**curr;

	curr = &tokens->head;
	while (*curr != NULL)
	{
		curr = &(*curr)->next;
	}
	*curr = token;
	token->prev = tokens->tail;
	tokens->tail = token;
}

void	free_tokens(t_Token_List *tokens)
{
	t_Token	*curr;
	t_Token	*token;

	curr = tokens->head;
	while (curr != NULL)
	{
		token = curr;
		curr = token->next;
		free_quote_list(&token->quotes);
		free(token->lexeme);
		free(token);
	}
	tokens->head = NULL;
	tokens->tail = NULL;
}
