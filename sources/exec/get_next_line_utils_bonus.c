/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:13:56 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/15 20:49:48 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*gnl_calloc(size_t count, size_t size)
{
	char	*i;
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = ptr;
	while (count--)
		*i++ = 0;
	return (ptr);
}

char	*gnl_strchr(const char *str, int c)
{
	while (*str && *str != (unsigned char) c)
		str++;
	if (*str == ((unsigned char) c))
		return ((char *) str);
	return (NULL);
}

char	*gnl_strjoin(char *str1, char const *str2)
{
	char	*joined_str;
	char	*ptr_to_joined_str;
	char	*ptr_to_str1;

	if (!str1 || !str2)
		return (NULL);
	joined_str = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	ptr_to_joined_str = joined_str;
	ptr_to_str1 = str1;
	while (*ptr_to_str1)
		*ptr_to_joined_str++ = *ptr_to_str1++;
	while (*str2)
		*ptr_to_joined_str++ = *str2++;
	*ptr_to_joined_str = '\0';
	free(str1);
	return (joined_str);
}

char	*gnl_substr(char const *str, unsigned int index, size_t len)
{
	char	*substr;
	char	*ptr_to_substr;

	if (!str || !len)
		return (NULL);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ptr_to_substr = substr;
	while (len--)
		*ptr_to_substr++ = *(str + index++);
	*ptr_to_substr = '\0';
	return (substr);
}
