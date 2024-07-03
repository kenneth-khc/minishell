/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:44:44 by qang              #+#    #+#             */
/*   Updated: 2024/07/02 17:49:03 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include <dirent.h>

int get_exit_status(void)
{
  return (*errnono());
}

void  set_exit_status(int status)
{
  *errnono() = status;
}

static int *errnono(void)
{
  static int exit_status = 0;

  return (&exit_status);
}

int pipepromax(int fd[2])
{
  if (pipe(fd) == -1)
  {
    dprintf(2, "pipe error\n");
    return (-1);
  }
  return (0);
}

int	exec_wait_pid(int last_pid, char *name)
{
	int	status;

	status = 0;
	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		else if (WTERMSIG(status) == 2)
			ft_putstr_fd("\n", STDERR_FILENO);
		// printf("error %d\n", WTERMSIG(status));
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

int	execvepromax(char *file, char **args, t_envar *path_node)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;
	char			*temp;
	char			*ret;

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
		while (entry != NULL)
		{
			if (ft_strcmp(entry->d_name, file) == 0)
			{
				temp = ft_strjoin(path, "/");
				ret = ft_strjoin(temp, file);
				execve(ret, args, NULL);
				free(ret);
				free(temp);
			}
			entry = readdir(dir);
		}
		closedir(dir);
		free(path);
		path = next_path(NULL);
	}
	return (-1);
}
