/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:15:25 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:19:44 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * Definitions to be used for certain characters and tokens,
 * as according to the Bash Reference Manual
 */

/**
 * Blanks are discarded and not included in words, unless quoted
 */
bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * A character that separates words when unquoted
 * & and ; are metacharacters too but we don't handle them
 */
bool	is_metacharacter(const char c)
{
	return (is_blank(c)
		|| c == '\n'
		|| c == '|'
		|| c == '('
		|| c == ')'
		|| c == '<'
		|| c == '>');
}
