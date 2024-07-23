/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 22:53:02 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "ft_dprintf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

void		redir(t_Redir_Node *node);
static void	write_heredoc(t_Redir_Node *node, int fd);
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

static void	write_heredoc(t_Redir_Node *node, int fd)
{
	char												*line;
	char												*expanded_line;
	int													i;

	i = 0;
	expanded_line = NULL;
	write(1, ">", 1);
	line = get_next_line(0);
	while (line != NULL && ft_strcmp(line, node->delim) != 10)
	{
		i++;
		expanded_line = expand_line(line, node->table);
		write(fd, expanded_line, ft_strlen(expanded_line));
		free(line);
		free(expanded_line);
		write(1, ">", 1);
		line = get_next_line(0);
	}
	if (line == NULL)
	{
		ft_dprintf(2, "%s: warning: here-document at line %d ", SHELL, i);
		ft_dprintf(2, "delimited by end-of-file (wanted `%s')\n", node->delim);
		exit(0);
	}
	free(line);
}

static void	redir_delim(t_Redir_Node *node)
{
	int		pid;
	char	*next_heredoc;
	int		fd;

	pid = forkpromax();
	if (pid == 0)
	{
		init_signal();
		next_heredoc = get_next_heredoc();
		fd = openpromax(next_heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
		write_heredoc(node, fd);
		close(fd);
		fd = openpromax(next_heredoc, O_RDONLY, 0644);
		unlink(next_heredoc);
		dup2(fd, node->oldfd);
		close(fd);
		if (node->left)
			exec_ast(node->left);
		exit(0);
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid));
	}
}

void	redir(t_Redir_Node *node)
{
	int	pid1;
	int	fd;

	if (node->heredoc)
	{
		redir_delim(node);
		return ;
	}
	pid1 = forkpromax();
	if (pid1 == 0)
	{
		check_permissions((char *)node->file, node->direction);
		fd = openpromax((char *)node->file, node->flags, node->mode);
		dup2(fd, node->oldfd);
		close(fd);
		if (node->left)
			exec_ast(node->left);
		exit(0);
	}
	else
	{
		ignore_sigs();
		set_exit_status(wait_for_child(pid1));
	}
}
