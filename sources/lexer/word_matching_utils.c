/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:56:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 10:44:11 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

static bool
only_digits(const char *str);

/**
 * Looks at a token and checks 
 * - if it is delimited by a redirector
 * - if it only consists of numbers
 * - if it is within fd range
 * if so, it is intended to be a file descriptor for redirection
**/
bool	io_number(char *lexeme, char *delim)
{
	return (only_digits(lexeme)
		&& (*delim == '>' || *delim == '<')
		&& ft_atoi(lexeme) < OPEN_MAX);
}

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
