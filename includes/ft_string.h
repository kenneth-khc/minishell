/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 05:56:16 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 06:16:08 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

/**
 * Represent a standard C string as a String object instead.
 * Encode the length of the string on initialization
 * to save on strlen calls when performing string manipulation
 * Technically a null terminator at the end of the string is
 * not necessary anymore, but it is kept for now as a lot of the current
 * functions assume null terminator for strings.
 * Store the address of the null terminator for easier bounds checking
 **/
typedef struct s_String
{
	char	*start;
	char	*end;
	size_t	len;
}	t_String;

t_String	*string(size_t len);
t_String	*stringify(char *s);
void		string_free(t_String *string);
t_String	*string_join(t_String *s1, t_String *s2);

#endif
