/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:04:33 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 06:05:29 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "get_next_line.h"
#include "input.h"
#include "ft_string.h"
#include "libft.h"
#include "execution.h"

#include "ft_dprintf.h"
void	get_input(t_Input *input)
{
	char		*line;
	char		*read;
	t_String	*str;
	static int i = 0;

	if (isatty(STDIN_FILENO))
	{
		ft_dprintf(STDERR_FILENO, ">> %d\n", ++i);
		read = readline("bish > ");
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		read = ft_strtrim(line, "\n");
		free(line);
	}
	if (read == NULL)
	{
		printf("exit\n");
		exit(get_exit_status());
	}
	str = stringify(read);
	free(read);
	str = string_join(str, stringify("\n"));
	store_input(input, str);
}

void	store_input(t_Input *input, t_String *new_line)
{
	t_String	**lines;
	int			i;

	i = 0;
	input->line_count++;
	lines = ft_calloc(1, sizeof(t_String **) * input->line_count);
	while (i < input->line_count - 1)
	{
		lines[i] = input->lines[i];
		i++;
	}
	free(input->lines);
	lines[i] = new_line;
	input->lines = lines;
}

t_String	*lines_to_string(t_Input *input)
{
	int			i;
	size_t		total_len;
	t_String	*str;
	char		*s;
	char		*ss;

	i = 0;
	total_len = 0;
	while (i < input->line_count)
		total_len += input->lines[i++]->len;
	str = string(total_len);
	s = str->start;
	i = 0;
	while (i < input->line_count)
	{
		ss = input->lines[i]->start;
		while (*ss)
			*s++ = *ss++;
		i++;
	}
	*s = '\0';
	return (str);
}

char	*input_to_history(t_Input *input)
{
	char	*line;

	line = lines_to_string(input)->start;
	return (ft_strtrim(line, "\n"));
}

void	clear_input(t_Input *input)
{
	int	i;

	i = 0;
	while (i < input->line_count)
	{
		free(input->lines[i]->start);
		free(input->lines[i]);
		i++;
	}
	free(input->lines);
	input->line_count = 0;
	input->lines = NULL;
}
