/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkify_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:32:18 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:32:41 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"

void	add_chunk(t_Chunk_List *chunks, char *str)
{
	t_Chunk	*new_chunk;

	new_chunk = ft_calloc(1, sizeof(*new_chunk));
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
	i = 0;
	while (chunk != NULL)
	{
		while (chunk->str && chunk->str[i] != '\0')
		{
			total_len++;
			i++;
		}
		chunk = chunk->next;
	}
	return (total_len);
}

