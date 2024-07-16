/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 01:08:06 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <stddef.h>

/**
 * A single line read as input.
 * To be stored in an array for cases where multiple lines are read.
 **/
typedef struct s_Line
{
	char	*start;
	size_t	len;
}	t_Line;

/**
 * Array storing all the lines read.
 **/
typedef struct s_Input
{
	t_Line	**lines; // array of lines that are input
	int		count; // size of the array
}	t_Input;

t_Line	*make_line(char *str);
void	get_input(t_Input *input);
t_Line	*get_input_line(int fd);
void	store_input(t_Input *input, t_Line *new_line);
void	clear_input(t_Input *input);

#endif
