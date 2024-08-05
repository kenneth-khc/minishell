/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 03:22:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:56:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "definitions.h"

static t_String
*get_var_value(char *key_start, t_entab *env);

static char
*copy_var_val(char *key, t_entab *env);

void	expand_variable(t_Expansion_List *expansions, t_Token *token,
					char *dollar, t_entab *env)
{
	t_String	*key;
	char		*key_start;
	char		*key_end;
	t_String	*value;
	t_Expansion	*new_expansion;

	key_end = ft_strpbrk(dollar + 1, is_not_identifier) - 1;
	key_start = ft_extract_substring(dollar, key_end);
	key = stringify(key_start);
	free(key_start);
	value = get_var_value(dollar + 1, env);
	if (value)
	{
		new_expansion = create_expansion(key, value,
				dollar - token->lex->start);
	}
	else
	{
		new_expansion = create_expansion(key, stringify(""),
				dollar - token->lex->start);
	}
	add_expansion(expansions, new_expansion);
	update_token_lexeme(token, expansions);
}

static t_String	*get_var_value(char *key_start, t_entab *env)
{
	char		*key_end;
	char		*key;
	char		*value;
	t_String	*string;

	key_end = ft_strpbrk(key_start, is_not_identifier) - 1;
	key = ft_extract_substring(key_start, key_end);
	if (key)
		value = copy_var_val(key, env);
	else
		value = NULL;
	free(key);
	string = stringify(value);
	free(value);
	return (string);
}

static char	*copy_var_val(char *key, t_entab *env)
{
	t_envar	*envar;
	char	*value;

	envar = get_var(key, env);
	if (envar && (envar->state & DISPLAY))
		value = envar->val;
	else
		value = NULL;
	if (value)
		value = ft_strdup(value);
	return (value);
}
