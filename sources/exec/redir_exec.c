/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 23:42:03 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void		redir(t_Redir_Node *node);
static void	check_permissions(char *newfile, char *oldfile);
static void	read_and_expand(t_Redir_Node *node);
static void	redir_delim(t_Redir_Node *node);
static char	*get_next_heredoc(void);

static char	*get_next_heredoc(void)
{
	static int	fd = 0;
	char		*num;
	char		*heredoc;

	num = ft_itoa(fd++);
	heredoc = ft_strjoin("/tmp/.heredoc", num);
	free(num);
	return (heredoc);
}

static void	read_and_expand(t_Redir_Node *node)
{
	char	*line;
	char	*expanded_line;

	write(1, ">", 1);
	line = get_next_line(0);
	if (line == NULL)
	{
		ft_dprintf(2, "%s: warning: here-document at line %d ", SHELL, 0);
		ft_dprintf(2, "delimited by end-of-file (wanted `%s')\n", node->delim);
		exit(0);
	}
	while (line != NULL
		&& ft_strncmp(line, node->delim, ft_strlen(node->delim)) != 0)
	{
		expanded_line = expand_line(line, node->table);
		write(node->newfd, expanded_line, ft_strlen(expanded_line));
		free(line);
		free(expanded_line);
		write(1, ">", 1);
		line = get_next_line(0);
	}
}

static void	redir_delim(t_Redir_Node *node)
{
	int		pid;
	char	*next_heredoc;

	pid = forkpromax();
	if (pid == 0)
	{
		next_heredoc = get_next_heredoc();
		node->newfd = open(next_heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (node->newfd < 0)
		{
			ft_dprintf(2, "Error while opening file\n");
			exit(1);
		}
		read_and_expand(node);
		close(node->newfd);
		node->newfd = open(next_heredoc, O_RDONLY, 0644);
		unlink(next_heredoc);
		dup2(node->newfd, node->oldfd);
		close(node->newfd);
		if (node->left)
			exec_ast(node->left);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

static void	check_permissions(char *newfile, char *oldfile)
{
	struct stat	file_stats;

	if (stat(newfile, &file_stats) == 0)
	{
		if (S_ISDIR(file_stats.st_mode))
		{
			ft_dprintf(2, "%s: %s: Is a directory\n", SHELL, newfile);
			exit(126);
		}
		else if (access(newfile, W_OK) == -1)
		{
			ft_dprintf(2, "%s: %s: Permission denied\n", SHELL, newfile);
			exit(126);
		}
	}
	if (stat(oldfile, &file_stats) != 0)
	{
		ft_dprintf(2, "%s: %s: No such file or directory\n", SHELL, oldfile);
		exit(126);
	}
	if (access(oldfile, R_OK) == -1)
	{
		ft_dprintf(2, "%s: %s: Permission denied\n", SHELL, oldfile);
		exit(126);
	}
}

void	redir(t_Redir_Node *node)
{
	int	pid1;

	if (node->delim)
	{
		redir_delim(node);
		return ;
	}
	pid1 = forkpromax();
	if (pid1 == 0)
	{
		check_permissions((char *)node->file, (char *)node->file);
		node->newfd = open(node->file, node->flags, node->mode);
		dup2(node->newfd, node->oldfd);
		close(node->newfd);
		if (node->left)
			exec_ast(node->left);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
}
