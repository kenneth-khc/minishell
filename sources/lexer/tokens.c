/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:43:38 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 18:09:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokens.h"
#include <stdlib.h>
#include "libft.h"

t_Token	*create_token(int type, const char *lexeme)
{
	t_Token	*new_token;

	new_token = ft_calloc(1, sizeof(*new_token));
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

int	get_tokens_count(t_Token_List *tokens)
{
	int		count;
	t_Token	*curr;

	count = 0;
	curr = tokens->head;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

void	print_tokens(t_Token_List *tokens)
{
	int			i;
	t_Token		*curr;

	i = 0;
	curr = tokens->head;
	while (curr != NULL)
	{
		printf("Token %d:\n", ++i);
		printf("%s\n", token_enum_to_str(curr));
		printf("%s\n", curr->lexeme);
		printf("\n");
		printf("↓\n\n");
		curr = curr->next;
	}
	printf("\n\n");
}

char	*token_enum_to_str(t_Token *token)
{
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

	return (ft_strdup(types[token->type - 256]));
}

