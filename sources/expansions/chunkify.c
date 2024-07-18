/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunkify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 17:54:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"
#include "definitions.h"

void	chunkify_unexpanded_portion(t_Chunk_List *chunks,
	char **start, char **end)
{
	char	*s;
	char	*e;

	s = *start;
	e = *end;
	add_chunk(chunks, ft_extract_substring(s, e - 1));
	*end += 1;
	*start = *end;
}

bool	chunkify_expansions(t_Chunk_List *chunks, t_entab *env,
	char **start, char **end)
{
	char	*s;
	char	*e;

	s = *start;
	e = *end;
	add_chunk(chunks, ft_extract_substring(s, e - 1));
	if (special_parameter(e))
	{
		expand_special_parameters(chunks, e);
		*end += 2;
		return (true);
	}
	else if (is_valid_key_start(e))
	{
		expand_parameter(chunks, env, e);
		*end = ft_strpbrk(e + 1, is_not_identifier);
		return (true);
	}
	else
	{
		add_chunk(chunks, ft_extract_substring(e, e));
		*end += 1;
	}
	return (false);
}

char	*join_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	size_t	total_len;
	int		i;
	int		j;
	char	*new_word;

	chunk = chunks->head;
	total_len = count_total_chunk_len(chunks);
	new_word = ft_calloc(total_len + 1, sizeof(*new_word));
	j = 0;
	while (chunk != NULL)
	{
		i = 0;
		while (chunk->str && chunk->str[i] != '\0')
		{
			new_word[j] = chunk->str[i];
			i++;
			j++;
		}
		chunk = chunk->next;
	}
	new_word[j] = '\0';
	return (new_word);
}

void	expand_parameter(t_Chunk_List *chunks, t_entab *env, char *dollar)
{
	char	*key_start;
	char	*key_end;
	char	*key;
	char	*value;

	key_start = dollar + 1;
	key_end = ft_strpbrk(key_start, is_not_identifier) - 1;
	key = ft_extract_substring(key_start, key_end);
	if (key)
	{
		value = copy_var_val(key, env);
		add_chunk(chunks, value);
	}
	else
		value = NULL;
	free(key);
}
