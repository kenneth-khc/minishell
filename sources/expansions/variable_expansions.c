/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:49:01 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 16:21:55 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "execution.h"
#include "expansions.h"
#include "libft.h"
#include "tokens.h"
#include "quotes.h"
#include "definitions.h"

bool	delimited(t_Range *p, t_Quote_List *pairs);
bool	is_dollar(char c);

bool	parameter_expand(t_Token *token, t_entab *env)
{
	t_Chunk_List	chunks;
	t_Range			p;
	bool			expanded;

	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	p = (t_Range){.start = token->lexeme, .end = token->lexeme};
	expanded = false;
	while (p.start < (token->lexeme + ft_strlen(token->lexeme)))
	{
		if (delimited(&p, &token->quotes))
		{
			add_chunk(&chunks, ft_extract_substring(p.start, p.end - 1));
			p.end += 1;
			p.start = p.end;
		}
		else if (is_dollar(*p.end))
			expanded = check_expansions(&p, &token->quotes, env, &chunks);
		else if (*p.end == '*' && !is_quoted(&token->quotes, p.end))
		{
			if (filename_expansion(&chunks, token))
			{
				while (*p.start == '*')
					p.start++;
				p.start++;
				p.end = p.start;
				expanded = true;
			}
			add_chunk(&chunks, ft_extract_substring(p.start, p.end));
			p.end += 1;
			p.start = p.end;
		}
		else
			p.end++;
	}
	free(token->lexeme);
	token->lexeme = join_chunks(&chunks);
	free_chunks(&chunks);
	return (expanded);
}

bool	is_dollar(char c)
{
	return (c == '$');
}

bool	delimited(t_Range *p, t_Quote_List *pairs)
{
	return (*p->end == '\0'
		|| (is_quote(*p->end) && quote_to_remove(pairs, p->end)));
}

bool	special_parameter(char *dollar)
{
	return (dollar[1] == '?'
		|| dollar[1] == '0'
		|| dollar[1] == '$');
}

void	expand_special_parameters(t_Chunk_List *chunks, char *dollar)
{
	char	*value;

	value = NULL;
	if (dollar)
	{
		if (dollar[1] == '?')
			value = ft_itoa(get_exit_status());
		else if (dollar[1] == '0')
			value = ft_strdup(SHELL);
		else if (dollar[1] == '$')
			value = ft_itoa(getpid());
		add_chunk(chunks, value);
	}
}
