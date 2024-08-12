/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:30:17 by qang              #+#    #+#             */
/*   Updated: 2024/08/12 15:31:13 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "libft.h"
#include <stdlib.h>

void		update_pwd(char **args, t_entab *table);
static void	update_pwd_args(t_envar *path_node, char *arg, t_entab *table);
static void	update_pwd_args_helper(t_envar *path_node, char *arg, char *curr);
static void	add_path(t_envar *path_node, char *arg);
static void	parse_prev_path(t_envar *path_node);

static void	parse_prev_path(t_envar *path_node)
{
	char	*temp;

	if (ft_strlen(path_node->val) == 1)
	{
		path_node->val = ft_strdup("/");
		return ;
	}
	temp = ft_strrchr(path_node->val, '/');
	if (temp == &path_node->val[0])
		path_node->val = ft_strdup("/");
	else
		path_node->val = ft_substr(path_node->val, 0, temp - path_node->val);
}

static void	add_path(t_envar *path_node, char *arg)
{
	char	*temp;

	if (ft_strcmp(arg, ".") != 0)
	{
    if (ft_strcmp(path_node->val, "/") != 0)
		  temp = ft_strjoin(path_node->val, "/");
    else
      temp = ft_strdup(path_node->val);
		path_node->val = ft_strjoin(temp, arg);
		free(temp);
	}
	else
		path_node->val = ft_strdup(path_node->val);
}

static void	update_pwd_args_helper(t_envar *path_node, char *arg, char *curr)
{
	char	*temp;

	while (*arg)
	{
		if (ft_strchr(arg, '/') == NULL)
			temp = ft_strdup(arg);
    else
			temp = ft_substr(arg, 0, ft_strchr(arg, '/') - arg);
		if (ft_strcmp(temp, "..") == 0)
			parse_prev_path(path_node);
		else
			add_path(path_node, temp);
		free(temp);
		free(curr);
		curr = path_node->val;
		if (!ft_strchr(arg, '/'))
			break ;
		arg = ft_strchr(arg, '/') + 1;
	}
}

static void	update_pwd_args(t_envar *path_node, char *arg, t_entab *table)
{
	char	*temp;

	temp = path_node->val;
	if (arg[0] != '/')
	{
		if (ft_strcmp(arg, ".") == 0)
			return ;
		update_pwd_args_helper(path_node, arg, ft_strdup(temp));
	}
	else
		path_node->val = ft_strdup(arg);
	update_oldpwd(temp, table);
	if (path_node->pwd)
	{
		free(path_node->pwd);
		path_node->pwd = NULL;
		path_node->state &= ~LOCAL;
	}
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
	while (ft_strlen(path_node->val) > 1
		&& !*(ft_strrchr(path_node->val, '/') + 1))
	{
		temp = path_node->val;
		path_node->val = ft_substr(path_node->val, 0,
				ft_strlen(path_node->val) - 1);
		free(temp);
	}
	free(path_node->pwd);
	path_node->pwd = NULL;
}
