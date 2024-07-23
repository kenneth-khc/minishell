/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:56:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 08:58:28 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

static bool	only_digits(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	io_number(char *lexeme, char *delim)
{
	return (only_digits(lexeme)
		&& (*delim == '>' || *delim == '<')
		&& ft_atoi(lexeme) < OPEN_MAX);
}
