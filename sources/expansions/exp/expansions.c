/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:05:03 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/05 09:52:20 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"
#include "expansions.h"

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
		tilde_expansion(&expansions, token, env);
		parameter_expansion(&expansions, token, env);
		get_next_expansion(NULL, RESET);
		filename_expand(token, tokens);
		remove_quotes(token);
		expansions = (t_Expansion_List){.head = NULL, .tail = NULL};
		token = token->next;
	}
}

/**
* Create a new structure storing the metadata of an expansion in a word
* offset tracks where the expansion begins relative to the start of the word
*/
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
