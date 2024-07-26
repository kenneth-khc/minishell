/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:20:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 10:11:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "definitions.h"

bool	is_not_identifier(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

/**
 * A key is only a valid name if it starts with an underscore or alphabet.
 * Treat the $ as literal and do not expand if it is not
 * going to be a valid name.
 * For some reason, $"" $'' expands.
**/
bool	is_valid_key_start(char *dollar)
{
	return (dollar[1] == '_'
		|| ft_isalpha(dollar[1]));
}

bool	is_valid_name(const char *start, const char *end)
{
	if (ft_isdigit(start[0]))
		return (false);
	while (start < end)
	{
		if (is_not_identifier(*start))
			return (false);
		start++;
	}
	return (true);
}

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_dollar(char c)
{
	return (c == '$');
}
