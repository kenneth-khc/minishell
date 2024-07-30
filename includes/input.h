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
# include <stdbool.h>
# include "ft_string.h"

/**
 * Information about the input goes here
 * Originally needed for handling multiline input due to unclosed quotes,
 * not really necessary right now
 */
typedef struct s_Input
{
	t_String	**lines; // array of lines that are input
	int			line_count; // size of the array
	bool		ok;
}	t_Input;

void		get_input(t_Input *input);
void		store_input(t_Input *input, t_String *new_line);
void		clear_input(t_Input *input);
void		add_input_to_history(t_Input *input);
t_String	*lines_to_string(t_Input *input);

#endif
