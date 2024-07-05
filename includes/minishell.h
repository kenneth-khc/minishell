/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:29:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/06 17:28:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "input.h"
# include "tokens.h"
# include "tree.h"

typedef struct s_Minishell
{
		
}	t_Minishell;

t_Token_List	scan(t_Input *input);

void	free_tokens(t_Token_List *tokens);
void	free_tree(t_Node *node);
char	*get_history(t_Input *input);


#endif
