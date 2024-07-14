/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:39:11 by qang              #+#    #+#             */
/*   Updated: 2024/07/15 02:05:17 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <termios.h>

# define SHELL "zish> "

typedef struct s_history
{
	char	*line;
	struct s_history	*next;
}	t_history;

void	push(t_history **a, t_history **b);
void	add_history(char *str, t_history **lst);

/*termios utils*/
void	set_rl_term(struct termios *orig_termios);
void	reset_terminal_mode(struct termios *orig_termios);
void	get_term_size(int *row, int *col);

/*standard utils*/
int ft_putchar(int c);
char	*append(char *str, char c);

/*termcap utils*/
void	move_cursor(int row, int col);
void	clear_scr(void);
void	ft_init_term(void);
void	clear_line(int row, int col);

/*tab to complete*/
void	complete_line(char *str);
#endif