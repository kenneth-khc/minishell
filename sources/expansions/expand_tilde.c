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
#include "ft_string.h"

static t_String
*get_home(t_entab *env);

/**
 * Expands the ~ character into the HOME environment variable
 */
void	tilde_expansion(t_Expansion_List *expansions,
		t_Token *token, t_entab *env)
{
	t_String	*expanded;
	t_Expansion	*expansion;

	if (token->lex->start[0] != '~')
		return ;
	expanded = get_home(env);
	expansion = create_expansion(stringify("~"), expanded, 0);
	add_expansion(expansions, expansion);
	update_token_lexeme(token, expansions);
}

static t_String	*get_home(t_entab *env)
{
	t_envar		*home_var;
	char		*val;
	t_String	*value;

	home_var = get_var("HOME", env);
	val = ft_strdup(home_var->val);
	if (val)
	{
		value = stringify(val);
	}
	else
	{
		value = stringify("");
	}
	free(val);
	return (value);
}
