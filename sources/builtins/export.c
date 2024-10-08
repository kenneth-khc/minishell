/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:05 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 16:43:30 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_dprintf.h"
#include <stdbool.h>
#include <stdlib.h>

int			ft_export(char **args, t_entab *table);
static bool	ft_is_valid_export(char *str);
static void	append_node(char *val, t_envar *node);
static void	append_var(char *arg, t_entab *table);
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
		if (str[i] == '+' && !str[i + 1])
			return (true);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	append_node(char *val, t_envar *node)
{
	char	*temp;

	if (ft_strcmp(node->key, "PWD") == 0)
	{
		if (node->pwd)
		{
			temp = node->pwd;
			node->pwd = ft_strjoin(node->pwd, val);
			free(temp);
		}
		else
			node->pwd = ft_strjoin(node->val, val);
	}
	if (node->val)
	{
		temp = node->val;
		node->val = ft_strjoin(node->val, val);
		free(temp);
	}
	else
		node->val = ft_strdup(val);
}

static void	append_var(char *arg, t_entab *table)
{
	char	*key;
	char	*val;
	char	*temp;

	key = ft_substr(arg, 0, ft_strchr(arg, '+') - arg);
	temp = ft_strchr(arg, '=');
	if (*(temp + 1) == '\0')
		val = ft_strdup("");
	else
		val = ft_substr(arg, temp + 1 - arg,
				ft_strlen(arg) - ft_strlen(key) - 2);
	if (get_var(key, table) == NULL)
	{
		temp = ft_strjoin("=", val);
		free(val);
		val = ft_strjoin(key, temp);
		add_var(val, table);
		free(temp);
	}
	else
		append_node(val, get_var(key, table));
	get_var(key, table)->state |= EXPORT;
	free(val);
	free(key);
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
		if (ft_strncmp("+=", &args[i][ft_strlen(temp) - 1], 2) == 0
			&& ft_is_valid_export(temp))
			append_var(args[i], table);
		else if (ft_is_valid_export(temp))
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
