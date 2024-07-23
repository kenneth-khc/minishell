/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:49:01 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 15:18:50 by qang             ###   ########.fr       */
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

bool	dollar_prefix_string(char *dollar, t_Quote_List *quote_list);

bool	parameter_expand(t_Token *token, t_entab *env)
{
	t_Chunk_List	chunks;
	t_Range			p;
	bool			expanded;

	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	p = (t_Range){.start = token->lexeme, .end = token->lexeme};
	expanded = false;
  (void)env;
	while (p.start < (token->lexeme + ft_strlen(token->lexeme)))
	{
		if (*p.end == '\0'
			|| (is_quote(*p.end) && quote_to_remove(&token->quotes, p.end)))
			chunkify_unexpanded_portion(&chunks, &p);
		else if (*p.end == '$')
			expanded = false;//check_expansions(&p, &token->quotes, env, &chunks);
		else
			p.end++;
	}
	free(token->lexeme);
	token->lexeme = join_chunks(&chunks);
	free_chunks(&chunks);
	return (expanded);
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
