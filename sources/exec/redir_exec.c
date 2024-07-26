/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/07/24 21:29:35 by qang             ###   ########.fr       */
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

#include "quotes.h"

void	heredoc_quote_removal(t_Redir_Node *node, t_Quotes *pair)
{
	char	*s;
	size_t	len;
	char	*unquoted_delim;

	s = node->delim;
	len = 0;
	while (*s)
	{
		if (s == pair->start || s == pair->end)
		{
			s++;
			continue ;
		}
		len++;
		s++;
	}
	unquoted_delim = ft_calloc(len + 1, sizeof(*unquoted_delim));
	char	*temp = unquoted_delim;
	s = node->delim;
	while (*s)
	{
		if (s == pair->start || s == pair->end)
		{
			s++;
			continue;
		}
		*temp = *s;
		temp++;
		s++;
	}
	free(node->delim);
	node->delim = unquoted_delim;
}

static void	write_heredoc(t_Redir_Node *node, int fd)
{
	char												*line;
	char												*expanded_line;
	static int											i = 0;
	t_Quotes	*quotes;
	bool		should_expand;

	should_expand = true;
	expanded_line = NULL;
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "> ", 2);
	line = get_next_line(0);
	node->delim = ft_strjoin(node->delim, "\n");
	// FIX: do expansions and quote removals on delim
	quotes = find_next_pair(node->delim, NULL);
	if (quotes && quotes->start && quotes->end)
	{
		should_expand = false;
		heredoc_quote_removal(node, quotes);
	}
	while (line != NULL && ft_strcmp(line, node->delim) != 0)
	{
		i++;
		if (should_expand)
			expanded_line = expand_line(line, node->table);
		else
		{
			expanded_line = line;
		}
		write(fd, expanded_line, ft_strlen(expanded_line));
		// free(line);
		// free(expanded_line);
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "> ", 2);
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

#include <stdio.h>
static void	redir_delim(t_Redir_Node *node)
{
	int		pid;
	char	*next_heredoc;
	int		fd;

		next_heredoc = get_next_heredoc();
		fd = openpromax(next_heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
		write_heredoc(node, fd);
		close(fd);
		fd = openpromax(next_heredoc, O_RDONLY, 0644);
		unlink(next_heredoc);
	pid = forkpromax();
	if (pid == 0)
	{
		init_signal();
		if (node->last_heredoc)
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
