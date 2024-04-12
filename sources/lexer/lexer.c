/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:43:38 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/12 10:42:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include "libft.h"

t_Token_list	scan(const char *line)
{
	t_Token_list	tokens;

	tokens = (t_Token_list){.head = NULL, .tail = NULL};
	while (*line != '\0')
	{
		while (*line == ' ')
			line++;
		if (*line == '|')
			scan_bar(&line, &tokens);
		else if (*line == '<')
			scan_lesser(&line, &tokens);
		else if (*line == '>')
			scan_greater(&line, &tokens);
		else
			scan_word(&line, &tokens);
		line++;
	}
	return (tokens);
}

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
}

void	print_tokens(t_Token_list *tokens)
{
	int	i = 0;
	t_Token		*curr;
	const char *types[] = {
		"WORD",
		"PIPE",
		"AND_AND",
		"OR_OR",
		"LESSER",
		"LESSER_LESSER",
		"GREATER",
		"GREATER_GREATER",
		"STAR"
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
