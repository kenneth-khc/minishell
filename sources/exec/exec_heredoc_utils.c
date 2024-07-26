/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:29:07 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/26 09:55:12 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "execution.h"
#include "expansions.h"

static void
heredoc_quote_removal(t_Heredoc *heredoc, t_Redir_Node *node);

void	heredoc_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "> ", 2);
}

t_Heredoc	*process_heredoc_delim(t_Redir_Node *node)
{
	t_Quotes	*pair;
	char		*p;
	t_Heredoc	*heredoc;

	p = node->delim;
	heredoc = ft_calloc(1, sizeof(*heredoc));
	pair = find_next_pair(p, &p);
	if (pair)
		heredoc->should_expand = false;
	else
		heredoc->should_expand = true;
	while (pair && p <= node->delim + ft_strlen(node->delim))
	{
		store_quotes(&heredoc->quotes, pair);
		pair = find_next_pair(p, &p);
	}
	if (heredoc->should_expand == false)
		heredoc_quote_removal(heredoc, node);
	return (heredoc);
}

static void	heredoc_quote_removal(t_Heredoc *heredoc, t_Redir_Node *node)
{
	t_Range			p;
	t_Chunk_List	chunks;

	p = (t_Range){.start = node->delim, .end = node->delim};
	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	while (p.start < (node->delim + ft_strlen(node->delim)))
	{
		if (delimited(&p) || quote_to_remove(&heredoc->quotes, p.end))
		{
			add_chunk(&chunks, ft_extract_substring(p.start, p.end - 1));
			point_to_new_chunk(&p);
		}
		else
			p.end++;
	}
	free(node->delim);
	node->delim = join_chunks(&chunks);
	heredoc->delim = node->delim;
	free_chunks(&chunks);
}

void	write_heredoc_to_file(t_Heredoc *heredoc, int fd, char *line, t_entab *table)
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
		write(fd, line, ft_strlen(expanded_line));
	}
	free(line);
	free(expanded_line);
}

