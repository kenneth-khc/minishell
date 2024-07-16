/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:28:14 by qang              #+#    #+#             */
/*   Updated: 2024/07/15 22:23:34 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "a.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int	ft_strncmp(const char *str1, const char *str2, int size)
{
	int	i;

	i = 0;
	while (i < size && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == size)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

typedef struct s_Redir_Delim
{
	char	**args;
	char	*delim;
	
}	t_Redir_Delim;

void	redir_delim(t_Redir_Delim *node, char **envp)
{
	int	fd;
	int pipefd[2];

	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error while opening file\n");
		exit(1);
	}
	char *line = get_next_line(0);
	while (ft_strncmp(line, node->delim, ft_strlen(node->delim)) != 0)
	{
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	read(fd, line, 100);
	close(fd);
	write(1, "line: ", 6);
	write(1, line, ft_strlen(line));
	close(fd);
	// fd = open(".heredoc", O_WRONLY | O_TRUNC);
	// close(fd);
	execve("rm", (char *[]){"rm", ".heredoc", NULL}, envp);
	perror("execve");
}

int	main(int ac, char **av, char **envp)
{
	t_Redir_Delim	node;

	if (ac < 3)
	{
		printf("Usage: %s <delim> <args...>\n", av[0]);
		exit(1);
	}
	node.delim = av[1];
	node.args = av + 2;
	redir_delim(&node, envp);
	// printf("%s\n", get_next_line(0));
	return (0);
}
