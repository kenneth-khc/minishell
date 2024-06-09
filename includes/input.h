/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/10 00:57:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include <readline/readline.h>
#include <stddef.h>

typedef struct	s_Line
{
	char			*start;
	size_t			len;
}	t_Line;

typedef struct s_Input
{
	t_Line	**lines; // array of lines that are input
	int		count; // size of the array
}	t_Input;

t_Line	*make_line(char *str);
void	get_input(t_Input *input);
t_Line	*get_input_line(int	fd);
void	store_input(t_Input *input, t_Line *new_line);
void	clear_input(t_Input *input);

#endif
