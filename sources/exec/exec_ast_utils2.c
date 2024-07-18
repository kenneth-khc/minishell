/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:42:15 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 21:39:28 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <unistd.h>

int		forkpromax(void);
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
