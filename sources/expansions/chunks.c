/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 10:15:12 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"

char	*join_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	size_t	total_len;
	int		i;
	int		j;
	char	*new_word;

	chunk = chunks->head;
	total_len = count_total_chunk_len(chunks);
	new_word = callocpromax(total_len + 1, sizeof(*new_word));
	j = 0;
	while (chunk != NULL)
	{
		i = 0;
		while (chunk->str && chunk->str[i] != '\0')
		{
			new_word[j++] = chunk->str[i++];
		}
		chunk = chunk->next;
	}
	new_word[j] = '\0';
	return (new_word);
}

void	free_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	t_Chunk	*temp;

	chunk = chunks->head;
	while (chunk)
	{
		temp = chunk;
		chunk = chunk->next;
		free(temp->str);
		free(temp);
	}
}

void	point_to_new_chunk(t_Range *p)
{
	p->end += 1;
	p->start = p->end;
}

void	add_chunk(t_Chunk_List *chunks, char *str)
{
	t_Chunk	*new_chunk;

	new_chunk = callocpromax(1, sizeof(*new_chunk));
	new_chunk->str = str;
	new_chunk->next = NULL;
	if (chunks->head == NULL)
		chunks->head = new_chunk;
	if (chunks->tail)
		chunks->tail->next = new_chunk;
	chunks->tail = new_chunk;
}

size_t	count_total_chunk_len(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	size_t	total_len;
	int		i;

	total_len = 0;
	chunk = chunks->head;
	while (chunk != NULL)
	{
		i = 0;
		while (chunk->str && chunk->str[i] != '\0')
		{
			total_len++;
			i++;
		}
		chunk = chunk->next;
	}
	return (total_len);
}
