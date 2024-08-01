/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:46:40 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/03 18:46:48 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	tilde_expansion(t_Expansion_List *expansions,
		t_Token *token, t_entab *env)
{
	t_String	*expanded;
	t_String	*new_lexeme;
	t_Expansion	*expansion;
	size_t		j;

	if (token->lexeme[0] != '~')
		return ;
	expanded = stringify((get_var("HOME", env)->val));
	new_lexeme = string(expanded->len + token->lex->len + 1 - 1);
	expansion = ft_calloc(1, sizeof(*expansion));
	expansion->start = new_lexeme->start;
	size_t	i = 0;
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
	token->lexeme = token->lex->start;
}
