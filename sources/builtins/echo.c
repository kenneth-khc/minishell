/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:52 by qang              #+#    #+#             */
/*   Updated: 2024/07/18 14:01:23 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

int	echo(char **args);

static int	skip_flags(char **args, int *newline)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0 && args[i + 1])
	{
		j = 1;
		if (args[i][j + 1] != '\0' && args[i][j + 1] != 'n')
			break ;
		else if (args[i][j + 1] != '\0')
		{
			while (args[i][j + 1] == 'n')
				j++;
			if (args[i][j + 1] != 0)
				return (i);
		}
		*newline = 0;
		i++;
	}
	return (i);
}

int	echo(char **args)
{
	int	newline;
	int	i;

	newline = 10;
	if (length(args) == 1)
	{
		printf("\n");
		return (0);
	}
	i = skip_flags(args, &newline);
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
