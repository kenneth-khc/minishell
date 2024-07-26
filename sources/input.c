/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:04:33 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:34:44 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "get_next_line.h"
#include "input.h"
#include "libft.h"
#include "execution.h"

t_Line	*make_line(char *str)
{
	t_Line	*line;

	line = ft_calloc(1, sizeof(*line));
	line->start = str;
	line->len = ft_strlen(str);
	return (line);
}

void	print_line(char *line);
void	get_input(t_Input *input)
{
	t_Line	*line;
	char	*read;
	char	*newline_appended;

	line = ft_calloc(1, sizeof(*line));
	// read = readline("bish> ");
	if (isatty(fileno(stdin)))
	{
		read = readline("bish > ");
	}
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		read = ft_strtrim(line, "\n");
		free(line);
	}
	if (read == NULL)
	{
		//printf("exit\n");
		exit(get_exit_status());
	}
	add_history(read);
	newline_appended = ft_strjoin(read, "\n");
	free(read);
	line->start = newline_appended;
	line->len = ft_strlen(line->start);
	store_input(input, line);
}

void	store_input(t_Input *input, t_Line *new_line)
{
	t_Line	**arr;
	int		i;

	i = 0;
	input->count++;
	arr = ft_calloc(1, sizeof(t_Line **) * input->count);
	while (i < input->count - 1)
	{
		arr[i] = input->lines[i];
		i++;
	}
	free(input->lines);
	arr[i] = new_line;
	input->lines = arr;
}

// For unterminated lines, fix later
t_Line	*get_input_line(int fd)
{
	t_Line	*line;

	line = ft_calloc(1, sizeof(*line));
	line->start = get_next_line(fd);
	line->len = ft_strlen(line->start);
	return (line);
}

void	clear_input(t_Input *input)
{
	int	i;

	i = 0;
	while (i < input->count)
	{
		free(input->lines[i]->start);
		free(input->lines[i]);
		i++;
	}
	free(input->lines);
	input->count = 0;
	input->lines = NULL;
}
