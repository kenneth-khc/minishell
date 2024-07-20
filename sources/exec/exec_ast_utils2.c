/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:42:15 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 12:09:43 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		forkpromax(void);
int		ft_strcmp2(const char *s1, const char *s2);
int		openpromax(char *file, int flags, mode_t mode);
void	close_pipe(int fd[2]);
void	pipepromax(int fd[2]);

void	pipepromax(int fd[2])
{
	int	err;

	err = pipe(fd);
	if (err == -1)
	{
		ft_dprintf(2, "pipe error");
		return ;
	}
}

int	forkpromax(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_dprintf(2, "fork error");
		return (-1);
	}
	return (pid);
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	openpromax(char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		ft_dprintf(2, "open error");
		exit(1);
	}
	return (fd);
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) == ft_tolower(*s2))
		{
			s1++;
			s2++;
		}
		else
			return (ft_tolower(*s1) - ft_tolower(*s2));
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
