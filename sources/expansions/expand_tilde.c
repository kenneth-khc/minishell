/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:46:40 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:01:01 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/**
 * Expands the ~ character into the HOME environment variable
 */
void	tilde_expansion(t_Expansion_List *expansions,
		t_Token *token, t_entab *env)
{
	t_String	*expanded;
	t_String	*new_lexeme;
	t_Expansion	*expansion;
	size_t		j;
	size_t		i;

	if (token->lex->start[0] != '~')
		return ;
	i = 0;
	expanded = stringify((get_var("HOME", env)->val));
	new_lexeme = string(expanded->len + token->lex->len + 1 - 1);
	expansion = ft_calloc(1, sizeof(*expansion));
	expansion->start = new_lexeme->start;
	while (expanded->start[i])
	{
		new_lexeme->start[i] = expanded->start[i];
		i++;
	}
	expansion->end = &new_lexeme->start[i - 1];
	add_expansion(expansions, expansion);
	j = 1;
	while (j < token->lex->len)
		new_lexeme->start[i++] = token->lex->start[j++];
	string_free(token->lex);
	token->lex = new_lexeme;
}
