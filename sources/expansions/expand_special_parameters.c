/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_parameters.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:16:10 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:59:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "expansions.h"

int
get_exit_status(void);

void	expand_special_parameter(t_Expansion_List *expansions, t_Token *token,
								char *dollar)
{
	t_String	*key;
	t_Expansion	*new_expansion;
	char		*value;
	t_String	*value_str;

	key = string_extract(dollar, dollar + 1);
	value = NULL;
	if (dollar[1] == '?')
		value = ft_itoa(get_exit_status());
	else if (dollar[1] == '0')
		value = ft_strdup(SHELL);
	else if (dollar[1] == '$')
		value = ft_itoa(getpid());
	if (value)
	{
		value_str = stringify(value);
		new_expansion = create_expansion(key, value_str,
				dollar - token->lex->start);
		free(value);
	}
	else
		new_expansion = create_expansion(key, stringify(""),
				dollar - token->lex->start);
	add_expansion(expansions, new_expansion);
	update_token_lexeme(token, expansions);
}
