/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:24:42 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/06 17:27:46 by kecheong         ###   ########.fr       */
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

