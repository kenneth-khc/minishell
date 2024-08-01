/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:47:00 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/03 19:15:08 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "definitions.h"
#include "libft.h"

#define GET	0
#define RESET 1
void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token				*token;
	t_Expansion_List	expansions;

	token = tokens->head;
	expansions = (t_Expansion_List){.head = NULL, .tail = NULL};
	while (token)
	{
		if (token->prev && token->prev->type == LESSER_LESSER)
		{
			token = token->next;
			continue ;
		}
		token->quotes = find_quoted_sections(token, &expansions);
		get_next_expansion(NULL, RESET);
		tilde_expansion(&expansions, token, env);
		parameter_expansion(&expansions, token, env);
		word_split(&expansions, token);
		token = token->next;
	}
}


t_String	*get_expansion(char *key_start, t_entab *env)
{
	char	*key_end;
	char	*key;
	char	*value;

	key_end = ft_strpbrk(key_start, is_not_identifier) - 1;
	key = ft_extract_substring(key_start, key_end);
	if (key)
		value = copy_var_val(key, env);
	else
		value = NULL;
	return (stringify(value));
}

void	parameter_expansion(t_Expansion_List *expansions, t_Token *token, t_entab *env)
{
	t_Range		p;
	t_Expansion	*new_expansion;
	t_String	*key;
	t_String	*value;

	p.start = token->lex->start;
	p.end = token->lex->end;
	while (*p.start)
	{
		if (is_expansion(p.start, &token->quotes))
		{
			if (is_identifier_start(p.start))
			{
				value = get_expansion(p.start + 1, env);
				key = stringify(ft_extract_substring(p.start, ft_strpbrk(p.start + 1, is_not_identifier) - 1));
				if (value)
				{
					new_expansion = create_expansion(key, value, p.start - token->lex->start);
					add_expansion(expansions, new_expansion);
					update_token_lexeme(token, expansions, &p);
				}
				else if (value == NULL)
				{
					new_expansion = create_expansion(key, stringify(""), p.start - token->lex->start);
					add_expansion(expansions, new_expansion);
					update_token_lexeme(token, expansions, &p);
				}
				if (expansions->tail && expansions->tail->end)
					p.start = expansions->tail->end + 1;
				else
					p.start++;
			}
		}
		else
			p.start++;
	}

}

bool	is_expansion_position(ssize_t i, t_Expansion_List *expansions)
{
	t_Expansion	*expansion;

	expansion = expansions->head;
	while (expansion)
	{
		if (i == expansion->offset)
			return (true);
		expansion = expansion->next;
	}
	return (false);
}

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

/*void	fill_and_track_expansion()*/
void	update_token_lexeme(t_Token *token, t_Expansion_List *expansions, t_Range *p)
{(void)p;
	ssize_t		new_len;
	t_String	*new_lexeme;
	char		*src;
	char		*dst;
	t_Expansion	*next_expansion;
	ssize_t		i;
	size_t		j;
	size_t		k;

	new_len = 0;
	i = 0;
	j = 0;
	new_len += calculate_unexpanded_len(token, token->lex);
	new_len += expansions->tail->value->len;
	new_lexeme = string(new_len);
	src = token->lex->start;
	dst = new_lexeme->start;
	next_expansion = get_next_expansion(expansions, GET);
	while (i < new_len)
	{
		while (next_expansion && i == next_expansion->offset)
		{
			k = 0;
			next_expansion->start = &dst[i];
			while (k < next_expansion->value->len)
			{
				dst[i] = next_expansion->value->start[k];
				i++;
				k++;
			}
			next_expansion->end = &dst[i - 1];
			if (next_expansion == expansions->tail)
				j += next_expansion->key->len;
			else
				j += next_expansion->value->len;
			next_expansion = get_next_expansion(expansions, GET);
		}
		while (j < token->lex->len)
		{
			if (next_expansion && i == next_expansion->offset)
				break ;
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	token->lex = new_lexeme;
	token->lexeme = token->lex->start;
	token->quotes = find_quoted_sections(token, expansions);
}


t_Expansion	*create_expansion(t_String *key, t_String *value, size_t offset)
{
	t_Expansion	*new_expansion;

	new_expansion = malloc(sizeof(*new_expansion));
	new_expansion->key = key;
	new_expansion->value = value;
	if (value == NULL)
		offset = -1;
	else
		new_expansion->offset = offset;
	new_expansion->start = NULL;
	new_expansion->end = NULL;
	new_expansion->next = NULL;
	return (new_expansion);
}

void	add_expansion(t_Expansion_List *expansions, t_Expansion *expansion)
{
	if (expansions->head == NULL)
		expansions->head = expansion;
	if (expansions->tail)
		expansions->tail->next = expansion;
	expansions->tail = expansion;
}

