/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:08:13 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/03 19:17:58 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokens.h"
#include "libft.h"

// Internal field seperator should default to whitespaces
#ifndef IFS
//# define IFS " \t\n"
# define IFS ' '
#endif

void	split_token_to_tokens(t_Token_List *tokens, t_Token *token,
			t_Token_List *new_tokens);

void	word_splitting(t_Token *token, t_Token_List *tokens)
{
	char			**words;
	char			**w;
	t_Token_List	new_tokens;
	t_Token			*new_token;

	new_tokens = (t_Token_List){.head = NULL, .tail = NULL};
	words = ft_split(token->lexeme, ' ');
	if (words == NULL)
		return ;
	w = words;
	while (*words)
	{
		new_token = create_token(WORD, *words);
		add_token(&new_tokens, new_token);
		words++;
	}
	free(w);
	split_token_to_tokens(tokens, token, &new_tokens);
}

void	split_token_to_tokens(t_Token_List *tokens, t_Token *old_token,
			t_Token_List *new_tokens)
{
	if (new_tokens->tail)
	{
		new_tokens->tail->next = old_token->next;
		if (old_token->prev)
			old_token->prev->next = new_tokens->head;
		else
			tokens->head = new_tokens->head;
		if (old_token->next)
			old_token->next->prev = new_tokens->tail;
		else
			tokens->tail = new_tokens->tail;
	}
	free_quote_list(&old_token->quotes);
	free(old_token->lexeme);
	free(old_token);
}
