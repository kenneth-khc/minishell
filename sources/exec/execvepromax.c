/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvepromax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:44:44 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:42:08 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_dprintf.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

void		execvepromax(char **args, t_entab *table, t_envar *path_node);
static void	attempt_exec(DIR *dir, char *path, char **args, t_entab *table);
static char	*next_path(char **path);
static void	print_error(char *command);

static char	*next_path(char **path)
{
	static char	*curr = NULL;
	char		*start;
	char		*end;
	size_t		len;

	if (path != NULL)
		curr = *path;
	if (curr == NULL || *curr == '\0')
		return (NULL);
	start = curr;
	end = ft_strchr(start, ':');
	if (end != NULL)
	{
		len = end - start;
		curr = end + 1;
	}
	else
	{
		len = ft_strlen(start);
		curr = NULL;
	}
	return (ft_substr(start, 0, len));
}

static void	attempt_exec(DIR *dir, char *path, char **args, t_entab *table)
{
	char			*temp;
	char			*ret;
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, args[0]) == 0)
		{
			temp = ft_strjoin(path, "/");
			ret = ft_strjoin(temp, args[0]);
			execve(ret, args, env_convert(table));
			free(ret);
			free(temp);
		}
		entry = readdir(dir);
	}
}

void	execvepromax(char **args, t_entab *table, t_envar *path_node)
{
	DIR		*dir;
	char	*path;

	if (path_node != NULL && path_node->state & DISPLAY)
	{
		path = next_path(&path_node->val);
		while (path != NULL)
		{
			dir = opendir(path);
			if (dir == NULL)
			{
				free(path);
				path = next_path(NULL);
				continue ;
			}
			attempt_exec(dir, path, args, table);
			closedir(dir);
			free(path);
			path = next_path(NULL);
		}
	}
	else
		print_error(args[0]);
}

static void	print_error(char *command)
{
	ft_dprintf(2, "%s: %s: command not found\n", SHELL, command);
	exit(127);
}
