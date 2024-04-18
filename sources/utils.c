/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:08:24 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 19:11:12 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Given two pointers to positions in a string,
 * extract all characters from <start> to <end> inclusive,
 * and returns it as a malloc'd string.
 * Assumes null terminated strings, so extraction will stop upon hitting
 * a null terminator, in case user passes in an invalid end pointer.
 **/
char	*extract_substring(const char *start, const char *end)
{
	const char	*curr = start;
	size_t		substr_len;
	char		*substr;
	char		*ret;

	if (start > end || start == NULL || end == NULL)
		return (NULL);
	substr_len = 0;
	while (curr <= end && *curr != '\0')
	{
		curr++;
		substr_len++;
	}
	substr = malloc(sizeof(char) * (substr_len + 1));
	if (substr == NULL)
		return (NULL);
	ret = substr;
	while (start <= end && *start != '\0')
	{
		*substr++ = *start++;
	}
	*substr = '\0';
	return (ret);
}
