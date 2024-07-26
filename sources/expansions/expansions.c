/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/24 19:09:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "expansions.h"
#include "tokens.h"
#include "definitions.h"

/**
* Go through the list of tokens and perform expansions and quote removals,
* following the order as specified by Bash as much as it can
* HACK: We ignore heredocs here because its' yet to be constructed tree node 
* requires information regarding its quotes and expansions that I cannot
* pass to from here, so we do that during the execution stage instead
**/
void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token	*token;
	bool	token_expanded;

	token = tokens->head;
	token_expanded = false;
	while (token)
	{
		if (token->prev && token->prev->type == LESSER_LESSER)
		{
			token = token->next;
			continue ;
		}
		tilde_expansion(token, env);
		token_expanded = do_expansions(token, env);
		if (token_expanded)
			word_splitting(token, tokens);
		token = token->next;
	}
}

bool	do_expansions(t_Token *token, t_entab *env)
{
	t_Range			p;
	t_Chunk_List	chunks;
	bool			expanded;

	expanded = false;
	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	p = (t_Range){.start = token->lexeme, .end = token->lexeme};
	while (p.start < (token->lexeme + ft_strlen(token->lexeme)))
	{
		if (delimited(&p) || quote_to_remove(&token->quotes, p.end))
		{
			add_chunk(&chunks, ft_extract_substring(p.start, p.end - 1));
			point_to_new_chunk(&p);
		}
		else if (is_dollar(*p.end))
			expanded = try_variable_expansion(&chunks, &token->quotes, env, &p);
		else if (*p.end == '*' && !is_quoted(&token->quotes, p.end))
			expanded = try_filename_expansion(&chunks, token, &p);
		else
			p.end++;
	}
	free(token->lexeme);
	token->lexeme = join_chunks(&chunks);
	free_chunks(&chunks);
	return (expanded);
}

bool	delimited(t_Range *p)
{
	return (*p->end == '\0');
}

void	tilde_expansion(t_Token *token, t_entab *env)
{
	if (token->word_flags & W_TILDE_EXPANSION)
		token->lexeme = ft_strdup(get_var("HOME", env)->val);
}
