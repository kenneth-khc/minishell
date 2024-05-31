/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:29:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:39:24 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

# include "lexer.h"

typedef struct s_Minishell
{
		
}	t_Minishell;

t_Line			*get_line(void);
t_Token_list	scan(t_Line	*line);


#endif
