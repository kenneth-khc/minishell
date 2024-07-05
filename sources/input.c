/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:04:33 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/06 17:40:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include "libft.h"
#include "input.h"
#include "errors.h"
#include <readline/history.h>

t_Line	*make_line(char *str)
{
	t_Line	*line;

	line = ft_calloc(1, sizeof(*line));
	if (line == NULL)
		error("calloc failed");
	line->start = str;
	line->len = ft_strlen(str);
	return (line);
}

void	get_input(t_Input *input)
{
	t_Line	*line;
	char	*read;
	char	*newline_appended;

	line = ft_calloc(1, sizeof(*line));
	if (line == NULL)
		error("calloc failed");
	read = readline("bish> ");
	if (read == NULL)
		printf("handle eof!\n"), exit(EXIT_FAILURE);
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
	if (arr == NULL)
		error("calloc failed\n");
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
t_Line	*get_input_line(int	fd)
{
	t_Line	*line;

	line = ft_calloc(1, sizeof(*line));
	if (line == NULL)
		error("calloc failed");
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

