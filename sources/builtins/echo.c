/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:52 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 22:25:35 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

int	echo(char **args)
{
	int	newline;
	int	i;

	newline = 10;
	i = 1;
	if (length(args) == 1)
	{
		printf("\n");
		return (0);
	}
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		i++;
		newline = 0;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("%c", newline);
	return (0);
}
