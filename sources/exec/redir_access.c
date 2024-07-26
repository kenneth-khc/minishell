/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:39:02 by qang              #+#    #+#             */
/*   Updated: 2024/07/18 17:53:27 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include "tree.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void	check_input(char *newfile)
{
	struct stat	file_stats;

	if (stat(newfile, &file_stats) != 0)
	{
		ft_dprintf(2, "%s: %s: No such file or directory\n", SHELL, newfile);
		exit(1);
	}
	if (access(newfile, R_OK) != 0)
	{
		ft_dprintf(2, "%s: %s: Permission denied\n", SHELL, newfile);
		exit(1);
	}
}

void	check_permissions(char *newfile, t_Direction direction)
{
	struct stat	file_stats;

	if (direction == OUTPUT)
	{
		if (stat(newfile, &file_stats) == 0 && S_ISDIR(file_stats.st_mode))
		{
			ft_dprintf(2, "%s: %s: Is a directory\n", SHELL, newfile);
			exit(1);
		}
		else if (access(newfile, F_OK) == 0 && access(newfile, W_OK) != 0)
		{
			ft_dprintf(2, "%s: %s: Permission denied\n", SHELL, newfile);
			exit(1);
		}
	}
	else
		check_input(newfile);
}
