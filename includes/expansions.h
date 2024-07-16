/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 01:08:41 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "env.h"
# include "tokens.h"
# include <stdbool.h>

void	expand(t_Token *token, char *expansion,
			char *expand_start, char *expand_end);
void	expand_tokens(t_Token_List *tokens, t_entab *env);
char	*copy_var_val(char *key, t_entab *env);
void	tilde_expansion(t_Token_List *tokens, t_entab *env);
void	parameter_expansion(t_Token_List *tokens, t_entab *env);
void	quote_removal(t_Token_List *tokens);
void	expand_exit_status(t_Token *token, char *dollar);
void	expand_pid(t_Token *token, char *dollar);
void	expand_shname(t_Token *token, char *dollar);
void	expand_variable(t_entab *env, t_Token *token, char *dollar);
bool	is_identifier_character(char c);
bool	is_not_identifier(char c);

#endif
