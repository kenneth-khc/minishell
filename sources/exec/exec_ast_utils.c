/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:44:44 by qang              #+#    #+#             */
/*   Updated: 2024/07/06 23:16:31 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include <dirent.h>

int	exec_wait_pid(int last_pid)
{
	int	status;

	status = 0;
	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_dprintf(2, "Quit: 3\n");
		else if (WTERMSIG(status) == 2)
			ft_dprintf(2, "\n");
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

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

static void	attempt_exec(struct dirent *entry, DIR *dir,
			char *path, char **args)
{
	char	*temp;
	char	*ret;

	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, args[0]) == 0)
		{
			temp = ft_strjoin(path, "/");
			ret = ft_strjoin(temp, args[0]);
			execve(ret, args, NULL);
			free(ret);
			free(temp);
		}
		entry = readdir(dir);
	}
}

int	execvepromax(char **args, t_envar *path_node)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;

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
		entry = readdir(dir);
		attempt_exec(entry, dir, path, args);
		closedir(dir);
		free(path);
		path = next_path(NULL);
	}
	return (-1);
}
