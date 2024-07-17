/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:49:01 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 10:40:17 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "expansions.h"
#include "libft.h"
#include "tokens.h"
#include <stdlib.h>

bool	parameter_expand(t_Token *token, t_entab *env)
{
	t_Chunk_List	chunks;
	char			*s;
	char			*e;
	bool			expanded;

	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	s = (char *)token->lexeme;
	e = s;
	expanded = false;
	while (s < (token->lexeme + ft_strlen(token->lexeme)))
	{
		if (*e == '\0'
			|| (is_quote(*e) && quote_to_remove(&token->quotes, e)))
		{
			add_chunk(&chunks, ft_extract_substring(s, e - 1));
			e++;
			s = e;
			continue ;
		}
		else if (*e == '$' && should_expand(e, &token->quotes))
		{
			// key = get_key()
			add_chunk(&chunks, ft_extract_substring(s, e - 1));
			if (e && e[1] == '?')
			{
				add_chunk(&chunks, ft_itoa(get_exit_status()));
				e += 2;
				s = e;
			}
			else if (e && e[1] == '0')
			{
				add_chunk(&chunks, ft_strdup(SHELL));
				e += 2;
				s = e;
			}
			else if (e && e[1] == '$')
			{
				add_chunk(&chunks, ft_itoa(getpid()));
				e += 2;
				s = e;
			}
			else
			{
				expand_into_chunk_list(&chunks, env, e);
				expanded = true;
				e++;
				e = ft_strpbrk(e, is_not_identifier);
				s = e;
			}
			continue ;
		}
		e++;
	}
	free((void *)token->lexeme);
	token->lexeme = join_chunks(&chunks);
	return (expanded);
}

char	*join_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	size_t	total_len;
	int		i;
	char	*new_word;

	i = 0;
	chunk = chunks->head;
	total_len = 0;
	while (chunk != NULL)
	{
		i = 0;
		if (chunk->str == NULL)
		{
			chunk = chunk->next;
			continue ;
		}
		while (chunk->str[i] != '\0')
		{
			total_len++;
			i++;
		}
		chunk = chunk->next;
	}
	chunk = chunks->head;
	new_word = ft_calloc(total_len + 1, sizeof(*new_word));
	int	j = 0;
	while (chunk != NULL)
	{
		i = 0;
		if (chunk->str == NULL)
		{
			chunk = chunk->next;
			continue ;
		}
		while (chunk->str[i] != '\0')
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

void	expand_into_chunk_list(t_Chunk_List *chunks, t_entab *env, char *dollar)
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

bool	quote_to_remove(t_Quote_List *quote_list, char *quote)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (quote == pair->start || quote == pair->end)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

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

#include "quotes.h"
bool	should_expand(char *dollar, t_Quote_List *quote_list)
{
	int			i = 0;
	t_Quotes	*pair;

	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (dollar > pair->start
			&& dollar < pair->end)
		{
			if (pair->quote == STRONG)
				return (false);
			else if (pair->quote == WEAK)
				return (true);
		}
		i++;
	}
	return (true);
}
