/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:05 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 21:23:23 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

static bool	ft_isstring(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	export(char **args, t_entab *table)
{
	int		i;
	char	*temp;
	int		errno;

	i = 1;
	errno = 0;
	if (length(args) == 1)
		print_sorted_env(table);
	else
	{
		while (args[i])
		{
			temp = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
			if (ft_isstring(args[i]))
				add_var(args[i], table);
			else
			{
				printf("export: `%s': not a valid identifier\n", args[i]);
				errno = 1;
			}
			free(temp);
			i++;
		}
	}
	return (errno);
}
