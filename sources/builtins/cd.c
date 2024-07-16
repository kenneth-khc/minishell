/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:12:37 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:50:56 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include <stdlib.h>

int			cd(char **args, t_entab *table);
void		update_oldpwd(char *oldpwd, t_entab *table);
void		add_pwd(t_entab *table);
static int	cd_home(t_entab *table);
static int	cd_home2(t_entab *table, char *path);

void	add_pwd(t_entab *table)
{
	char	cwd[PATH_MAX];
	char	*temp;

	if (getcwd(cwd, PATH_MAX - 1))
	{
		temp = ft_strjoin("PWD=", cwd);
		add_var(temp, table);
		get_var("PWD", table)->state &= ~DISPLAY;
	}
	else
	{
		ft_dprintf(2, "%s: cd: error retrieving current directory: ", SHELL);
		ft_dprintf(2, "getcwd: cannot access parent directories: ");
		ft_dprintf(2, "No such file or directory\n");
	}
}

void	update_oldpwd(char *oldpwd, t_entab *table)
{
	t_envar		*path_node;
	char		*temp;

	path_node = get_var("OLDPWD", table);
	if (path_node == NULL)
	{
		temp = ft_strjoin("OLDPWD=", oldpwd);
		add_var(temp, table);
		get_var("OLDPWD", table)->state &= ~DISPLAY;
	}
	else
	{
		temp = path_node->val;
		path_node->val = ft_strdup(oldpwd);
	}
	if (temp)
		free(temp);
}

static int	cd_home2(t_entab *table, char *path)
{
	char	*temp;
	char	*temp2;
	int		errno;

	temp = ft_strjoin(get_var("PWD", table)->val, "/");
	temp2 = ft_strjoin(temp, path);
	if (ft_strlen(temp2) >= PATH_MAX - 1)
	{
		ft_dprintf(2, "%s: cd: %s: File name too long\n", SHELL, path);
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

	path_node = get_var("HOME", table);
	if (path_node == NULL
		|| (path_node != NULL && !(path_node->state & DISPLAY)))
	{
		ft_dprintf(2, "%s: cd: HOME not set\n", SHELL);
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

	errno = 0;
	if (length(args) == 1)
		errno = cd_home(table);
	else if (length(args) == 2)
		errno = chdir(args[1]);
	else if (length(args) > 2)
	{
		ft_dprintf(2, "%s: cd: too many arguments\n", SHELL);
		return (2);
	}
	if (errno)
	{
		if (args[1] && ft_strlen(args[1]) > 255)
			ft_dprintf(2, "%s: cd: %s: File name too long\n", SHELL, args[1]);
		else if (errno != 1)
			ft_dprintf(2, "%s: cd: %s: No such file or directory\n",
				SHELL, args[1]);
		return (1);
	}
	update_pwd(args, table);
	return (errno);
}
