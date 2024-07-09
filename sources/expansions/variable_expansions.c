/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:49:01 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/09 21:57:01 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "a.h"
#include "expansions.h"
#include <stdlib.h>

void	parameter_expansion(t_Token_List *tokens, t_entab *env)
{
	t_Token		*curr;
	char		*dollar;

	curr = tokens->head;
	while (curr != NULL)
	{
		while (curr->lexeme && curr->word_flags & W_HAS_DOLLAR && !(curr->word_flags & W_STRONG_QUOTED))
		{
			dollar = ft_strchr(curr->lexeme, '$');
			if (dollar && dollar[1] == '?')
				expand_exit_status(curr, dollar);
			else if (dollar && dollar[1] == '0')
				expand(curr, SHELL, dollar, dollar + 1);
			else if (dollar && is_identifier_character(dollar[1]))
				expand_variable(env, curr, dollar);
			else if (dollar && dollar[1] == '$')
				expand_pid(curr, dollar);
			else
				curr->word_flags &= ~W_HAS_DOLLAR;
		}
		curr = curr->next;
	}
}

void	expand_exit_status(t_Token *token, char *dollar)
{
	char	*exit_status;

	exit_status = ft_itoa(get_exit_status());
	expand(token, exit_status, dollar, dollar + 1);
	free(exit_status);
}

void	expand_pid(t_Token *token, char *dollar)
{
	char	*pid;

	pid = ft_itoa(getpid());
	expand(token, pid, dollar, dollar + 1);
	free(pid);
}

void	expand(t_Token *token, char *expansion, char *expand_start, char *expand_end)
{
	char	*front;
	char	*back;
	char	*lexeme_end;

	front = ft_extract_substring(token->lexeme, expand_start - 1);
	lexeme_end = (char *)token->lexeme + ft_strlen(token->lexeme) - 1;
	back = ft_extract_substring(expand_end + 1, lexeme_end);
	token->lexeme = ft_strjoin_multiple(3, front, expansion, back);
	free(front);
	free(back);
	return ;
}

void	expand_variable(t_entab *env, t_Token *token, char *dollar)
{
	char	*key_start;
	char	*key_end;
	char	*key;
	char	*value;

	key_start = dollar + 1;
	key_end = ft_strpbrk(key_start, is_not_identifier) - 1;
	key = ft_extract_substring(key_start, key_end);
	value = copy_var_val(key, env);
	expand(token, value, key_start - 1, key_end);
	free(key);
}

// void	expand_shname(t_Token *token, char *dollar)
// {
// 	char	*front;
// 	char	*back;
// 	char	*expand_end;
// 	char	*expanded;
// 	char	*lex_end;
//
// 	front = ft_extract_substring(token->lexeme, dollar - 1);
// 	expand_end = dollar + 1;
// 	expanded = "bish";
// 	lex_end = (char *) token->lexeme + ft_strlen(token->lexeme) - 1;
// 	back = ft_extract_substring(expand_end + 1, lex_end);
// 	token->lexeme = ft_strjoin_multiple(3, front, expanded, back);
// 	free(front);
// 	free(back);
// }

