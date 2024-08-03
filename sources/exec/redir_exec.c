/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/08/03 16:33:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "ft_dprintf.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

void		redir(t_Redir_Node *node);
static void	write_heredoc(t_Redir_Node *node, int fd);
static void	write_heredoc_to_file(t_Heredoc *heredoc, int fd,
				char *line, t_entab *table);
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
	static int											i = 0;
	t_Heredoc											*heredoc;

	heredoc_prompt();
	heredoc = process_heredoc_delim(node);
	line = get_next_line(0);
	while (line != NULL && ft_strcmp(line, node->delim) != 0)
	{
		i++;
		write_heredoc_to_file(heredoc, fd, line, node->table);
		heredoc_prompt();
		line = get_next_line(0);
	}
	if (line == NULL)
	{
    node->delim[ft_strlen(node->delim) - 1] = '\0';
		ft_dprintf(2, "%s: warning: here-document at line %d ", SHELL, i);
		ft_dprintf(2, "delimited by end-of-file (wanted `%s')\n", node->delim);
	}
	free(line);
}

static void	write_heredoc_to_file(t_Heredoc *heredoc, int fd,
		char *line, t_entab *table)
{
	char	*expanded_line;

	if (heredoc->should_expand)
	{
		expanded_line = expand_line(line, table);
		write(fd, expanded_line, ft_strlen(expanded_line));
	}
	else
	{
		expanded_line = NULL;
		write(fd, line, ft_strlen(line));
	}
	free(line);
	free(expanded_line);
}

static void	redir_delim(t_Redir_Node *node)
{
	pid_t	pid;
	char	*next_heredoc;
	int		fd;

  int pid1 = forkpromax();
  next_heredoc = get_next_heredoc();
  if (pid1 == 0)
  {
    set_sig();
    fd = openpromax(next_heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write_heredoc(node, fd);
    close(fd);
    exit(0);
  }
  else
  {
    ignore_sigs();
    set_exit_status(wait_for_child(pid1));
  }
  if (get_exit_status() == 130)
    return ;
  init_signal();
  if (special_cmd(node))
  {
    node->file = next_heredoc;
    redir_special_cmd(node);
    return ;
  }
	pid = forkpromax();
	if (pid == 0)
	{
		fd = openpromax(next_heredoc, O_RDONLY, 0644);
		unlink(next_heredoc);
		init_signal();
		if (node->last_heredoc)
			dup2(fd, node->oldfd);
		close(fd);
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
  if (special_cmd(node))
  {
    redir_special_cmd(node);
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
