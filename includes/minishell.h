/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:29:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 01:09:52 by qang             ###   ########.fr       */
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

void			free_tokens(t_Token_List *tokens);
char			*get_history(t_Input *input);
void			expand_tokens(t_Token_List *tokens, t_entab *env);
void			tilde_expansion(t_Token_List *tokens, t_entab *env);
void			parameter_expansion(t_Token_List *tokens, t_entab *env);
void			expand_exit_status(t_Token *token, char *dollar);
void			expand_pid(t_Token *token, char *dollar);
void			expand_shname(t_Token *token, char *dollar);
void			expand_variable(t_entab *env, t_Token *token, char *dollar);
bool			is_identifier_character(char c);

#endif
