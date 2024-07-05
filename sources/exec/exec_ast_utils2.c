/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:46:52 by qang              #+#    #+#             */
/*   Updated: 2024/07/06 00:50:17 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

static int	*errnono(void);

int	get_exit_status(void)
{
	return (*errnono());
}

void	set_exit_status(int status)
{
	*errnono() = status;
}

static int	*errnono(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

void	pipepromax(int fd[2])
{
	int	err;

	err = pipe(fd);
	if (err == -1)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
}

int	forkpromax(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		dprintf(STDERR_FILENO, "error");
		return (-1);
	}
	return (pid);
}
