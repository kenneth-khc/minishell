/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:05:03 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:58:08 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "env.h"
#include "expansions.h"

static bool
is_word(t_Token *token);

static bool
is_heredoc_delim(t_Token *token);

t_Quote_List
find_quoted_sections(t_Token *token, t_Expansion_List *expansions);

/**
* Go through the list of tokens and perform expansions and quote removals,
* following the order as specified by Bash as much as it can
* HACK: We ignore heredoc delimiters here because its' yet to be constructed 
* tree node requires information regarding its quotes and expansions that can't
* be passed to from here, so we do that during the execution stage instead
**/
void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token				*token;
	t_Expansion_List	expansions;

	token = tokens->head;
	expansions = (t_Expansion_List){.head = NULL, .tail = NULL};
	while (token)
	{
		if (is_word(token) || is_heredoc_delim(token))
		{
			token->quotes = find_quoted_sections(token, &expansions);
			tilde_expansion(&expansions, token, env);
			parameter_expansion(&expansions, token, env);
			filename_expansion(token, tokens);
			quote_removal(token);
			clear_expansion_list(&expansions);
		}
		token = token->next;
	}
}

static bool	is_word(t_Token *token)
{
	return (token->type == WORD || token->type == ASSIGNMENT_WORD);
}

static bool	is_heredoc_delim(t_Token *token)
{
	return (token->prev && token->prev->type == LESSER_LESSER);
}
