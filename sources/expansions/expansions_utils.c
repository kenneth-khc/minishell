/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/15 21:12:55 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "tokens.h"
#include "libft.h"
#include "env.h"

bool	is_identifier_character(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_not_identifier(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

bool	word_is_quoted(t_Token *token)
{
	return (token->type == WORD
		&& (token->word_flags & W_STRONG_QUOTED
			|| token->word_flags & W_WEAK_QUOTED));
}

char	*copy_var_val(char *key, t_entab *env)
{
	t_envar	*envar;
	char	*value;

	envar = get_var(key, env);
	if (envar && (envar->state & DISPLAY))
		value = envar->val;
	else
		value = NULL;
	if (value)
		ft_strdup(value);
	return (value);
}

