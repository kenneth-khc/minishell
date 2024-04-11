/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:43:38 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/11 11:14:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include "libft.h"

t_Token_list	scan(const char *line)
{
	t_Token_list	tokens = {.head = NULL, .tail = NULL};
	t_Token			*token;
	char	**splitted;

	splitted = ft_split(line, ' ');
	while (*splitted)
	{
		token = create_token(WORD, "test");
		add_to_list(&tokens, token);
		splitted++;
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
	static int i = 1;
	new_token->num = i++;
	return (new_token);
}

void	add_to_list(t_Token_list *tokens, t_Token *token)
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
	static int	i = 0;
	t_Token	*curr;

	curr = tokens->head;
	while (curr != NULL)
	{
		printf("Token %d:\n", ++i);
		printf("ID: %d\n", curr->num);
		printf("%d\n", curr->type);
		printf("%s\n", curr->lexeme);
		printf("\n");
		curr = curr->next;
	}
}