/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 01:31:30 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

void		read_and_expand(t_Redir_Node *node, int fd);
void		redir(t_Redir_Node *node);
void		redir_delim(t_Redir_Node *node);
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

// char	*expand(char *line, t_entab *table)
// {
// 	char	*expanded_line;
	
// }

void	read_and_expand(t_Redir_Node *node, int fd)
{
	char	*line;
	char	*expanded_line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_dprintf(2, "%s: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", SHELL, 0, node->delim);
		exit(0);
	}
	while (line != NULL && ft_strncmp(line, node->delim, ft_strlen(node->delim)) != 0)
	{
		// expanded_line = expand(line, NULL);
		write(node->newfd, expanded_line, ft_strlen(expanded_line));
		free(line);
		line = get_next_line(fd);
	}
}

void	redir_delim(t_Redir_Node *node)
{
	int		fd;
	int		pid;
	char	*next_heredoc;

	pid = forkpromax();
	if (pid == 0)
	{
		next_heredoc = get_next_heredoc();
		fd = open(next_heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_dprintf(2, "Error while opening file\n");
			exit(1);
		}
		read_and_expand(node, fd);
		close(fd);
		fd = open(next_heredoc, O_RDONLY);
		unlink(next_heredoc);
		dup2(fd, node->oldfd);
		close(fd);
		if (node->left)
			exec_ast(node->left);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	redir(t_Redir_Node *node)
{
	int	pid1;

	if (node->delim)
	{
		redir_delim(node);
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		node->newfd = open(node->file, node->flags, node->mode);
		dup2(node->newfd, node->oldfd);
		close(node->newfd);
		if (node->left) // there could be no cmd to execute
			exec_ast(node->left);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
}