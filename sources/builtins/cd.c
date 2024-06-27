/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:12:37 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 01:45:12 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

static int	cd_home2(t_entab *table, char *path)
{
	char	*temp;
	char	*temp2;
	int		errno;

	temp = ft_strjoin(get_var("PWD", table)->val, "/");
	temp2 = ft_strjoin(temp, path);
	if (ft_strlen(temp2) >= PATH_MAX - 1)
	{
		printf("cd: %s: File name too long\n", path);
		free(temp2);
		free(temp);
		return (1);
	}
	errno = chdir(temp2);
	free(temp);
	free(temp2);
	return (errno);
}

static int	cd_home(t_entab *table)
{
	t_envar	*path_node;
	int		errno;

	errno = 0;
	path_node = get_var("HOME", table);
	if (path_node == NULL || (path_node != NULL && !path_node->display))
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	if (path_node->val[0] != '/' && !ft_strcmp(path_node->val, ".")
		&& !ft_strcmp(path_node->val, ".."))
		return (cd_home2(table, path_node->val));
	return (chdir(path_node->val));
}

int	cd(char **args, t_entab *table)
{
	int		errno;
	t_envar	*path_node;

	errno = 0;
	if (length(args) == 1)
		errno = cd_home(table);
	else if (length(args) == 2)
		errno = chdir(args[1]);
	else if (length(args) > 2)
	{
		printf("cd: too many arguments\n");
		return (2);
	}
	if (errno)
	{
		if (args[1] && ft_strlen(args[1]) > 255)
			printf("cd: %s: File name too long\n", args[1]);
		else if (errno != 1)
			printf("cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	update_pwd(args, table);
	return (errno);
}
