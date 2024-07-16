/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/09 21:23:04 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"

bool	is_identifier_character(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_not_identifier(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

char	*copy_var_val(char *key, t_entab *env)
{
	t_envar	*envar;
	char	*value;

	envar = get_var(key, env);
	if (envar)
		value = envar->val;
	else
		value = NULL;
	if (value)
		ft_strdup(value);
	return (value);
}

