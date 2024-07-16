/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:05 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:52:05 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_dprintf.h"
#include <stdbool.h>
#include <stdlib.h>

int			ft_export(char **args, t_entab *table);
static bool	ft_is_valid_export(char *str);
static void	ft_export_error(char *str, int *errno);

static void	ft_export_error(char *str, int *errno)
{
	ft_dprintf(2, "%s: export: `%s': not a valid identifier\n", SHELL, str);
	*errno = 1;
}

static bool	ft_is_valid_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0' || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (false);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_export(char **args, t_entab *table)
{
	int		i;
	char	*temp;
	int		errno;

	i = 1;
	errno = 0;
	if (length(args) == 1)
		return (print_sorted_env(table));
	while (args[i])
	{
		temp = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
		if (ft_is_valid_export(temp))
		{
			add_var(args[i], table);
			get_var(temp, table)->state |= EXPORT;
		}
		else
			ft_export_error(args[i], &errno);
		free(temp);
		i++;
	}
	return (errno);
}
