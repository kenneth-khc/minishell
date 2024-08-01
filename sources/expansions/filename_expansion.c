/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:04:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/05 09:31:27 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "tokens.h"
#include "expansions.h"

static void	add_spaces_between_chunks(t_Chunk_List *chunks);

bool	try_filename_expansion(t_Chunk_List *chunks, t_Token *token, t_Range *p)
{
	bool	token_expanded;

	token_expanded = filename_expansion(chunks, token);
	if (token_expanded)
	{
		while (*p->end == '*')
			p->end++;
		p->end++;
		p->start = p->end;
		token_expanded = true;
	}
	add_chunk(chunks, ft_extract_substring(p->start, p->end));
	p->end += 1;
	p->start = p->end;
	return (token_expanded);
}

bool	filename_expansion(t_Chunk_List *chunks, t_Token *token)
{
	char			**files;
	char			**ff;
	t_Chunk_List	filename_chunks;

	files = match_expression(token->lexeme);
	if (ft_strcmp(*files, token->lexeme) == 0)
		return (false);
	ff = files;
	filename_chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	while (*files)
		add_chunk(&filename_chunks, *files++);
	add_spaces_between_chunks(&filename_chunks);
	if (filename_chunks.tail)
	{
		if (chunks->tail)
			chunks->tail->next = filename_chunks.head;
		else
			chunks->head = filename_chunks.head;
		chunks->tail = filename_chunks.tail;
	}
	free(ff);
	return (true);
}

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

static void	add_spaces_between_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	t_Chunk	*space;

	chunk = chunks->head;
	while (chunk->next)
	{
		space = callocpromax(1, sizeof(*space));
		space->str = callocpromax(1, sizeof(char));
		space->str[0] = ' ';
		space->next = chunk->next;
		chunk->next = space;
		chunk = space->next;
	}
}
