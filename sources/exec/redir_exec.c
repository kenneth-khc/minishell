/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:10:41 by qang              #+#    #+#             */
/*   Updated: 2024/08/03 17:01:18 by codespace        ###   ########.fr       */
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
void		write_heredoc_loop(t_Redir_Node *node, int fd);
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

void	write_heredoc_loop(t_Redir_Node *node, int fd)
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
	char	*next_heredoc;

	next_heredoc = get_next_heredoc();
	write_heredoc(node, next_heredoc);
	if (get_exit_status() == 130)
		return ;
	init_signal();
	if (special_cmd(node))
	{
		node->file = next_heredoc;
		redir_special_cmd(node);
		return ;
	}
	run_heredoc(node, next_heredoc);
}

void	redir(t_Redir_Node *node)
{
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
	run_redir(node);
}
