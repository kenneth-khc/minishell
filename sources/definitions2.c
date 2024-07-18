/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:20:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:54:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "definitions.h"

bool	is_identifier_character(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_not_identifier(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

bool	is_valid_name(const char *start, const char *end)
{
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
