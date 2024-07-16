/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:15 by qang              #+#    #+#             */
/*   Updated: 2024/07/15 16:14:26 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>

void  start(t_readline_info *rl_info)
{
	ft_init_term();
	get_term_size(&rl_info->row, &rl_info->col);
	set_rl_term(&rl_info->orig_termios);
}

void	print_prompt(t_readline_info* rl_info)
{
	rl_info->cur_x = write(1, rl_info->prompt, strlen(rl_info->prompt));
}

void	backspace(char **line, t_readline_info* rl_info)
{
	if (rl_info->cur_x > rl_info->pad)
	{
		rl_info->cur_x--;
		(*line)[strlen(*line) - 1] = '\0';
		clear_line(rl_info->cur_y, rl_info->pad);
		write(1, *line, strlen(*line));
	}
}

void  handle_special_char(int c, char **line, t_readline_info* rl_info)
{
	static t_history	*up_history = NULL;
	static t_history  *down_history = NULL;

	if (c == 4)
	{
		reset_terminal_mode(&rl_info->orig_termios);
		exit(0);
	}
	else if (c == 9)
		complete_line(*line);
	else if (c == 127)
		backspace(line, rl_info);
	else if (c == 10 || c == 13)
	{
		write(1, "\r\n", 2);
		rl_info->cur_y++;
		rl_info->cur_x = 0;
		for (t_history *tmp = down_history; tmp != NULL; tmp = tmp->next)
			push(&down_history, &up_history);
		if (up_history && strcmp(up_history->line, "") == 0)
			up_history->line = *line;
		else
			add_history(*line, &up_history);
		*line = strdup("");
		print_prompt(rl_info);
	}
	else if (c == 27)
	{
		if (read(STDIN_FILENO, &c, 1) > 0 && c == 91)
		{
			read(STDIN_FILENO, &c, 1);
			switch (c)
			{
				case 'A':
				{
					if (down_history == NULL)
						add_history(*line, &down_history);
					push(&up_history, &down_history);
					if (down_history != NULL)
					{
						clear_line(rl_info->cur_y, rl_info->pad);
						write(1, down_history->line, strlen(down_history->line));
						*line = down_history->line;
						rl_info->cur_x = strlen(*line) + rl_info->pad;
					}
					break ;
				}
				case 'B':
				{
					push(&down_history, &up_history);
					if (down_history != NULL)
					{
						clear_line(rl_info->cur_y, rl_info->pad);
						write(1, down_history->line, strlen(down_history->line));
						*line = down_history->line;
						rl_info->cur_x = strlen(*line) + rl_info->pad;
					}
					break ;
				}
				case 'C':
					if (rl_info->cur_x < 100 - rl_info->pad && rl_info->cur_x < strlen(*line) + rl_info->pad)
						rl_info->cur_x++;
					break ;
				case 'D':
					if (rl_info->cur_x > rl_info->pad)
						rl_info->cur_x--;
					break ;
			}
			move_cursor(rl_info->cur_y, rl_info->cur_x);
		}
	}
}

char  *start_read(t_readline_info *rl_info)
{
	char  c;
	char *line;
	
	line = strdup("");
	while (read(STDIN_FILENO, &c, 1) > 0 && c != 'q')
	{
		if (ft_iscntrl(c))
			handle_special_char(c, &line, rl_info);
		else
		{
			write(1, &c, 1);
			line = append(line, c);
			rl_info->cur_x++;
		}
	}
	return (NULL);
}

char	*readline(char *prompt)
{
	t_readline_info rl_info;

	start(&rl_info);
	rl_info.prompt = prompt;
	rl_info.pad = strlen(prompt);
	clear_scr();
	print_prompt(&rl_info);
	start_read(&rl_info);
	reset_terminal_mode(&rl_info.orig_termios);
	return (NULL);
}

// char	*readline(char *str)
// {
// 	char	c;
// 	char	*line = strdup("");
// 	int cur_x = 0, cur_y = 0;
// 	static t_history	*up_history = NULL;
// 	static t_history  *down_history = NULL;
// 	clear_scr();
// 	for (size_t i = 0; i < strlen(str); i++)
// 	{
// 		ft_putchar(str[i]);
// 		cur_x++;
// 	}
// 	const int pad = cur_x;
// 	while (read(STDIN_FILENO, &c, 1) > 0 && c != 'q')
// 	{
// 		if (c == 4)
// 			break ;
// 		if (c == 9)
// 			complete_line(line);
// 		if (c == 127)
// 		{
// 			if (cur_x > pad)
// 			{
// 				cur_x--;
// 				line[strlen(line) - 1] = '\0';
// 				clear_line(cur_y, pad);
// 				write(1, line, strlen(line));
// 			}
// 		}
// 		if (iscntrl(c))
// 		{
// 			if (c == 27)
// 			{
// 				if (read(STDIN_FILENO, &c, 1) > 0 && c == 91)
// 				{
// 					read(STDIN_FILENO, &c, 1);
// 					switch (c)
// 					{
// 						case 'A':
// 						{
// 							if (down_history == NULL)
// 							{
// 								add_history(line, &down_history);
// 							}
// 							push(&up_history, &down_history);
// 							if (down_history != NULL)
// 							{
// 								clear_line(cur_y, pad);
// 								write(1, down_history->line, strlen(down_history->line));
// 								line = down_history->line;
// 								cur_x = strlen(line) + pad;
// 							}
// 							break ;
// 						}
// 						case 'B':
// 						{
// 							push(&down_history, &up_history);
// 							if (down_history != NULL)
// 							{
// 								clear_line(cur_y, pad);
// 								write(1, down_history->line, strlen(down_history->line));
// 								line = down_history->line;
// 								cur_x = strlen(line) + pad;
// 							}
// 							break ;
// 						}
// 						case 'C':
// 							if (cur_x < 100 - pad && cur_x < strlen(line) + pad)
// 								cur_x++;
// 							break ;
// 						case 'D':
// 							if (cur_x > pad)
// 								cur_x--;
// 							break ;
// 					}
// 					move_cursor(cur_y, cur_x);
// 				}
// 			}
// 			else if (c == 10 || c == 13)
// 			{
// 				write(1, "\r\n", 2);
// 				cur_y++;
// 				cur_x = 0;
// 				for (t_history *tmp = down_history; tmp != NULL; tmp = tmp->next)
// 				{
// 					push(&down_history, &up_history);
// 				}
// 				if (up_history && strcmp(up_history->line, "") == 0)
// 					up_history->line = line;
// 				else
// 					add_history(line, &up_history);
// 				line = strdup("");
// 				for (size_t i = 0; i < strlen(str); i++)
// 				{
// 					ft_putchar(str[i]);
// 					cur_x++;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			write(1, &c, 1);
// 			line = append(line, c);
// 			cur_x++;
// 		}
// 	}
// 	return (NULL);
// }

int	main(int ac, char **av, char **envp)
{
	// int		row;
	// int		col;
	
	// ft_init_term();
	// get_term_size(&row, &col);
	// set_rl_term(&orig_termios);
	readline(SHELL);
	// reset_terminal_mode(&orig_termios);
	return (0);
}
