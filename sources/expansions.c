/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/08 18:43:13 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include "debug.h"
#include "tokens.h"
#include "minishell.h"
#include "lexer.h"

void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
	t_Token	*curr; (void)curr;

	curr = tokens->head;
	tilde_expansion(tokens, env);
	parameter_expansion(tokens, env);
}

void	tilde_expansion(t_Token_List *tokens, t_entab *env)
{
	t_Token	*curr;

	curr = tokens->head;
	while (curr != NULL)
	{
		if (curr->word_flags & W_TILDE_EXPANSION)
		{
			curr->lexeme = ft_strdup(get_var("HOME", env)->val);
		}
		curr = curr->next;
	}
}

void	parameter_expansion(t_Token_List *tokens, t_entab *env)
{(void)env;
	t_Token		*curr;
	const char	*start;
	const char	*dollar;
	const char	*end;
	const char	*expanded;
	const char	*remain;
	void		*to_free;

	curr = tokens->head;
	while (curr != NULL)
	{
		while (curr->lexeme && curr->word_flags & W_HAS_DOLLAR)
		{
			start = curr->lexeme;
			dollar = ft_strchr(curr->lexeme, '$');
			if (dollar && dollar[1] == '?')
			{
				end = dollar + ft_strlen(dollar) - 1;
				expanded = ft_itoa(get_exit_status());
				to_free = (void *)expanded;
				remain = ft_extract_substring(start, dollar - 1);
				expanded = ft_strjoin_unsafe(expanded, remain);
				free(to_free);
				free((void *)remain);
				curr->lexeme = ft_extract_substring(dollar + 2, end);
				to_free = (void *)curr->lexeme;
				curr->lexeme = ft_strjoin_unsafe(expanded, curr->lexeme);
				free(to_free);
			}
			else
				curr->word_flags &= ~W_HAS_DOLLAR;
		}
		curr = curr->next;
	}
}

