/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:15:25 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 00:28:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

/**
 * Definitions to be used for certain characters and tokens,
 * as according to the Bash Reference Manual
 */

/* Blanks are discarded and not included in words, unless quoted */
bool	is_blank(const char c)
{
	return (c == ' ' || c == '\t');
}

/* A character that separates words when unquoted */
bool	is_metacharacter(const char c)
{
	return (is_blank(c)
			|| c == '\n'
			|| c == '|'
			|| c == '&'
			|| c == ';'
			|| c == '('
			|| c == ')'
			|| c == '<'
			|| c == '>');
}

/* A token that performs a control function */
bool	is_control_operator(const char *str)
{
	return (ft_strcmp(str, "||")
			|| ft_strcmp(str, "&&")
			|| ft_strcmp(str, "&")
			|| ft_strcmp(str, ";")
			|| ft_strcmp(str, ";;")
			|| ft_strcmp(str, ";&")
			|| ft_strcmp(str, ";;&")
			|| ft_strcmp(str, "|")
			|| ft_strcmp(str, "|&")
			|| ft_strcmp(str, "(")
			|| ft_strcmp(str, ")"));
}

/* A token that performs redirection */
bool	is_redirection_operator(const char *str)
{
	return (ft_strcmp(str, "<")
			|| ft_strcmp(str, ">")
			|| ft_strcmp(str, ">|")
			|| ft_strcmp(str, "<<")
			|| ft_strcmp(str, ">>")
			|| ft_strcmp(str, "<&")
			|| ft_strcmp(str, ">&")
			|| ft_strcmp(str, "<<-")
			|| ft_strcmp(str, "<>"));
}

bool	is_operator(const char *str)
{
	return (is_control_operator(str)
			|| is_redirection_operator(str));
}
