/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 06:30:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <stddef.h>
# include "ft_string.h"

/**
 * Array storing all the lines read for one complete command.
 **/
typedef struct s_Input
{
	t_String	**lines; // array of lines that are input
	int			line_count; // size of the array
}	t_Input;

void		get_input(t_Input *input);
void		store_input(t_Input *input, t_String *new_line);
void		clear_input(t_Input *input);
char		*input_to_history(t_Input *input);
t_String	*lines_to_string(t_Input *input);

#endif
