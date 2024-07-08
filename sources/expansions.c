/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/08 19:17:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include "debug.h"
#include "libft.h"
#include "tokens.h"
#include "minishell.h"
#include "lexer.h"

void	expand_tokens(t_Token_List *tokens, t_entab *env)
{
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
{
	t_Token		*curr;
	const char	*start; (void)start;
	char		*dollar;

	curr = tokens->head;
	while (curr != NULL)
	{
		while (curr->lexeme && curr->word_flags & W_HAS_DOLLAR)
		{
			start = curr->lexeme;
			dollar = ft_strchr(curr->lexeme, '$');
			if (dollar && dollar[1] == '?')
				expand_exit_status(curr, dollar);
			else if (dollar && (ft_isalnum(dollar[1]) || dollar[1] == '_'))
				expand_variable(env, curr, dollar);
			else
				curr->word_flags &= ~W_HAS_DOLLAR;
		}
		curr = curr->next;
	}
}

void	expand_exit_status(t_Token *token, char *dollar)
{
	char	*end;
	char	*expanded;
	char	*remain;
	void	*to_free;

	end = dollar + ft_strlen(dollar) - 1;
	expanded = ft_itoa(get_exit_status());
	to_free = expanded;
	remain = ft_extract_substring(token->lexeme, dollar - 1);
	expanded = ft_strjoin_unsafe(expanded, remain);
	free(to_free);
	free(remain);
	token->lexeme = ft_extract_substring(dollar + 2, end);
	to_free = (void *)token->lexeme;
	token->lexeme = ft_strjoin_unsafe(expanded, token->lexeme);
	free(to_free);
}

void	expand_variable(t_entab *env, t_Token *token, char *dollar)
{
	t_envar	*envar;
	const char	*name_start = dollar + 1;
	const char	*name_end = name_start;
	char	*remain;
	char	*key;
	char	*value;

	while (is_identifier_character(*name_end))
		name_end++;
	name_end--;
	key = ft_extract_substring(name_start, name_end);
	envar = get_var(key, env);
	if (envar)
		value = envar->val;
	else
		value = NULL;
	if (value)
		value = ft_strdup(value);
	remain = ft_extract_substring(token->lexeme, dollar - 1);
	value = ft_strjoin_unsafe(value, remain);
	token->lexeme = ft_extract_substring(dollar + ft_strlen(key) + 1, dollar + ft_strlen(dollar) - 1);
	token->lexeme = ft_strjoin_unsafe(value, token->lexeme);
}

bool	is_identifier_character(char c)
{
	return (ft_isalnum(c) || c == '_');
}

