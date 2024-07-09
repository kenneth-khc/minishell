/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:30:17 by qang              #+#    #+#             */
/*   Updated: 2024/07/06 00:00:57 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include <stdlib.h>

static void	add_pwd(t_entab *table)
{
	char	cwd[PATH_MAX];
	char	*temp;

	if (getcwd(cwd, PATH_MAX - 1))
	{
		temp = ft_strjoin("PWD=", cwd);
		add_var(temp, table);
		get_var("PWD", table)->display = false;
	}
	else
	{
		printf("%s: cd: error retrieving current directory: getcwd: ", SHELL);
		printf("cannot access parent directories: No such file or directory");
	}
}

static void	update_oldpwd(char *oldpwd, t_entab *table)
{
	t_envar		*path_node;
	char		*temp;

	path_node = get_var("OLDPWD", table);
	if (path_node == NULL)
	{
		temp = ft_strjoin("OLDPWD=", oldpwd);
		add_var(temp, table);
		get_var("OLDPWD", table)->display = false;
	}
	else
	{
		temp = path_node->val;
		path_node->val = ft_strdup(oldpwd);
	}
	free(temp);
}

static void	update_pwd_args(t_envar *path_node, char *arg, t_entab *table)
{
	char	*temp;
	char	*temp2;

	temp = path_node->val;
	if (arg[0] != '/')
	{
		if (ft_strcmp(arg, "..") == 0)
		{
			temp2 = ft_strrchr(temp, '/');
			path_node->val = ft_substr(temp, 0, temp2 - temp);
		}
		else if (ft_strcmp(arg, ".") != 0)
		{
			temp2 = ft_strjoin(temp, "/");
			path_node->val = ft_strjoin(temp2, arg);
			free(temp2);
		}
		else
			return ;
	}
	else
		path_node->val = ft_strdup(arg);
	update_oldpwd(temp, table);
	free(temp);
}

void	update_pwd(char **args, t_entab *table)
{
	t_envar	*path_node;
	char	*temp;

	path_node = get_var("PWD", table);
	if (path_node == NULL)
		add_pwd(table);
	else if (length(args) == 2)
		update_pwd_args(path_node, args[1], table);
	else
		update_pwd_args(path_node, get_var("HOME", table)->val, table);
	while (!*(ft_strrchr(path_node->val, '/') + 1))
	{
		temp = path_node->val;
		path_node->val = ft_substr(path_node->val, 0,
				ft_strlen(path_node->val) - 1);
		free(temp);
	}
}
