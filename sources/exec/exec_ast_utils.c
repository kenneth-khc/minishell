/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:46:52 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:40:08 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <sys/wait.h>

int			get_exit_status(void);
int			wait_for_child(int last_pid);
void		set_exit_status(int status);
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

int	wait_for_child(int last_pid)
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
