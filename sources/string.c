/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 02:10:42 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 05:45:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "input.h"

/**
** Creates a String object with size len
**/
t_String	*string(size_t len)
{
	t_String	*str;

	str = ft_calloc(1, sizeof(*str));
	str->len = len;
	str->start = ft_calloc(len + 1, sizeof(char));
	str->end = str->start + len;
	return (str);
}

/**
** Takes a pointer to a string and creates a String object of it
** Store the length of the String in len
** Store the end of the String signified by a '\0'
**/
t_String	*stringify(char *s)
{
	t_String	*str;
	size_t		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = string(ft_strlen(s));
	while (s[i])
	{
		str->start[i] = s[i];
		i++;
	}
	str->end = str->start + str->len;
	return (str);
}

/**
** Frees the malloc'd buffer in the String object and the String itself
**/
void	string_free(t_String *string)
{
	free(string->start);
	string->start = NULL;
	string->end = NULL;
	string->len = 0;
	free(string);
}

/**
** Joins the contents of two Strings together and frees them,
** returning a newly joined String
**/
t_String	*string_join(t_String *s1, t_String *s2)
{
	t_String	*new_string;
	size_t		new_len;
	char		*s;
	size_t		i;

	new_string = ft_calloc(1, sizeof(*new_string));
	new_len = s1->len + s2->len;
	i = 0;
	new_string->start = ft_calloc(new_len + 1, sizeof(char));
	new_string->len = new_len;
	s = new_string->start;
	while (s1->start[i] != '\0')
		*s++ = s1->start[i++];
	i = 0;
	while (s2->start[i] != '\0')
		*s++ = s2->start[i++];
	*s = '\0';
	new_string->end = s;
	string_free(s1);
	string_free(s2);
	return (new_string);
}
