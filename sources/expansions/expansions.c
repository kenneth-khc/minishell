/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:45:41 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/09 22:01:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "a.h"
#include "libft.h"
#include "tokens.h"
#include "expansions.h"

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

// todo: word splitting
// todo: filename expansion (*)
// todo: pattern matching
// todo: quote removal

