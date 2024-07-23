/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:04:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 11:42:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "tokens.h"
#include "expansions.h"

bool	is_quoted(t_Quote_List *quote_list, char *c)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (c > pair->start && c < pair->end)
			return (true);
		i++;
	}
	return (false);
}

void	split_token_to_tokens(t_Token_List *tokens, t_Token *token,
			t_Token_List *new_tokens);

void	print_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*c;

	c = chunks->head;
	while (c)
	{
		printf("%s ", c->str);
		printf("-> ");
		c = c->next;
	}
	fflush(stdout);
}

bool	filename_expansion(t_Chunk_List *chunks, t_Token *token)
{
	char			**words; 
	char			**w;
	t_Chunk_List	filename_chunks;

	words = match_expression(token->lexeme);
	if (ft_strcmp(token->lexeme, *words) == 0)// when there is no match it returns back the original lexeme
		return (false);
	w = words;
	filename_chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	while (*words)
	{
		add_chunk(&filename_chunks, *words);
		words++;
	}
	words = w;
	t_Chunk	*chunk;
	t_Chunk	*curr;
	curr = filename_chunks.head;
	while (curr)
	{
		chunk = ft_calloc(1, sizeof(*chunk));
		chunk->str = ft_calloc(1, sizeof(char));
		chunk->str[0] = ' ';
		chunk->next = curr->next;
		curr->next = chunk;
		curr = chunk->next;
	}
	if (filename_chunks.tail)
	{
		filename_chunks.tail->next = NULL;
		if (chunks->tail)
			chunks->tail->next = filename_chunks.head;
		else
		{
			chunks->head = filename_chunks.head;
			chunks->tail = filename_chunks.tail;
		}
	}
	//print_chunks(&filename_chunks);
	free(w);
	return (true);
}
