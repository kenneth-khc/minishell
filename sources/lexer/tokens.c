/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:43:38 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/19 17:57:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokens.h"
#include <stdlib.h>

t_Token	*create_token(int type, const char *lexeme)
{
	t_Token	*new_token;

	new_token = malloc(sizeof(*new_token));
	new_token->type = type;
	new_token->lexeme = lexeme;
	new_token->next = NULL;
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
	token->next = NULL;
	tokens->tail = token;
}

void	print_tokens(t_Token_List *tokens)
{
	int	i = 0;
	t_Token		*curr;
	const char *types[] = {
		"WORD",
		"PIPE",
		"OR_OR",
		"AND_AND",
		"LESSER",
		"LESSER_LESSER",
		"GREATER",
		"GREATER_GREATER",
		"STAR",
		"OPEN_PARAN",
		"CLOSE_PARAN",
		"SEMICOLON",
		"END_OF_LINE",
		"HASH"
	};
	curr = tokens->head;
	while (curr != NULL)
	{
		printf("Token %d:\n", ++i);
		printf("%s\n", types[curr->type - 256]);
		printf("%s\n", curr->lexeme);
		printf("\n");
		printf("↓\n\n");
		curr = curr->next;
	}
	printf("\n\n");
}
