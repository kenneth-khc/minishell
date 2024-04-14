/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:43:38 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/15 21:05:26 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include "libft.h"

t_Token	*create_token(int type, const char *lexeme)
{
	t_Token	*new_token;

	new_token = malloc(sizeof(*new_token));
	new_token->type = type;
	new_token->lexeme = lexeme;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_Token_list *tokens, t_Token *token)
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

void	print_tokens(t_Token_list *tokens)
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
		"END_OF_LINE"
	};
	curr = tokens->head;
	while (curr != NULL)
	{
		printf("Token %d:\n", ++i);
		printf("%s\n", types[curr->type - 256]);
		printf("%s\n", curr->lexeme);
		printf("\n");
		curr = curr->next;
	}
	printf("\n\n");
}
