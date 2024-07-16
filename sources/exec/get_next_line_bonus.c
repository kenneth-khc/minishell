/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:12:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/15 20:51:40 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int ft_strlen(const char *s)
{
  int i;

  i = 0;
  while (s[i])
    i++;
  return (i);
}

void	extract_line(char **buffer, char **line, ssize_t *bytes)
{
	size_t	line_len;
	char	*remain;

	if (*bytes <= 0)
	{
		*line = gnl_substr(*buffer, 0, ft_strlen(*buffer));
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	line_len = 0;
	while ((*buffer)[line_len] && (*buffer)[line_len] != '\n')
		line_len++;
	*line = gnl_substr(*buffer, 0, line_len + 1);
	remain = gnl_substr(*buffer, line_len + 1, ft_strlen(*buffer) - line_len);
	free(*buffer);
	*buffer = remain;
}

void	read_file(int fd, char **line, char **buffer)
{
	char	*temp;
	ssize_t	bytes;

	temp = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return ;
	bytes = 1;
	while (bytes > 0)
	{
		*buffer = gnl_strjoin(*buffer, temp);
		if (gnl_strchr(*buffer, '\n'))
			break ;
		bytes = read(fd, temp, BUFFER_SIZE);
		temp[bytes] = '\0';
	}
	free(temp);
	temp = NULL;
	extract_line(buffer, line, &bytes);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[10240];

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (!buffer[fd])
	{
		buffer[fd] = gnl_calloc(1, sizeof(char));
		if (!buffer[fd])
			return (NULL);
	}
	read_file(fd, &line, &buffer[fd]);
	return (line);
}
