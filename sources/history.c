/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:42 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 01:24:18 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"

char	*get_history(t_Input *input)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = "";
	while (i < input->count)
	{
		buffer = ft_strjoin(buffer, input->lines[i]->start);
		i++;
	}
	return (buffer);
}
