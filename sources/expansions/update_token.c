/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:28:50 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:57:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "expansions.h"
#include "definitions.h"

/**
 * Update the token's lexeme after performing an expansion with the newly
 * expanded value in the token
 * Does each expansion sequentially
 * After copying the word into a new buffer, its addresses will change,
 * therefore we look at the offset of the expansion to continue tracking it,
 * so that we can know which quotes are "real" quotes and which resulted from
 * an expansion
 **/

static void
copy_old_to_new(char *dst, char *dst_end, char *src,
	t_Expansion_List *expansions);

static void
copy_expansion_to_string(char *dst, t_Expansion *expansion, ssize_t *lex_i);

t_Quote_List
find_quoted_sections(t_Token *token, t_Expansion_List *expansions);

static size_t	calculate_new_len(t_Token *token, t_Expansion *expansion)
{
	char	*p;
	ssize_t	i;
	size_t	len;

	len = 0;
	i = 0;
	p = token->lex->start;
	while (&p[i] < token->lex->end)
	{
		if (i == expansion->offset)
		{
			len += expansion->value->len;
			i += expansion->key->len;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

void	update_token_lexeme(t_Token *token, t_Expansion_List *expansions,
						t_Expansion *new_expansion)
{
	t_String	*new_lexeme;

	new_lexeme = string(calculate_new_len(token, new_expansion));
	copy_old_to_new(new_lexeme->start, new_lexeme->end,
		token->lex->start, expansions);
	string_free(token->lex);
	token->lex = new_lexeme;
	free_quote_list(&token->quotes);
	token->quotes = find_quoted_sections(token, expansions);
}

/**
 * Copy the old word into a new String with the new expanded value
 */
static void	copy_old_to_new(char *dst, char *dst_end,
						char *src, t_Expansion_List *expansions)
{
	ssize_t		i;
	size_t		j;
	t_Expansion	*expansion;

	i = 0;
	j = 0;
	expansion = get_next_expansion(expansions, GET);
	while (&dst[i] < dst_end)
	{
		if (expansion && i == expansion->offset)
		{
			copy_expansion_to_string(dst, expansion, &i);
			if (expansion == expansions->tail)
				j += expansion->key->len;
			else
				j += expansion->value->len;
			expansion = get_next_expansion(expansions, GET);
		}
		else
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
}

/**
 * Copy the new expanded value from the expansion list into the new String
 */
static void	copy_expansion_to_string(char *dst, t_Expansion *expansion,
								ssize_t *lex_i)
{
	size_t	exp_i;

	exp_i = 0;
	expansion->start = &dst[*lex_i];
	while (exp_i < expansion->value->len)
	{
		dst[*lex_i] = expansion->value->start[exp_i];
		(*lex_i)++;
		exp_i++;
	}
	expansion->end = &dst[*lex_i - 1];
}

/**
 * HACK: get the next expansion to process in the list of all expansions
 * reset it by clearing the static variable once done processing
 * this is quite disturbing and I wouldn't do it like this if I had more time
 */
t_Expansion	*get_next_expansion(t_Expansion_List *expansions, bool reset)
{
	static t_Expansion	*next_expansion = NULL;

	if (reset)
	{
		next_expansion = NULL;
		return (NULL);
	}
	if (next_expansion == expansions->tail)
	{
		next_expansion = NULL;
		return (NULL);
	}
	else if (next_expansion == NULL)
	{
		next_expansion = expansions->head;
	}
	else if (next_expansion)
	{
		next_expansion = next_expansion->next;
	}
	while (next_expansion && next_expansion->offset == -1)
		next_expansion = next_expansion->next;
	return (next_expansion);
}
