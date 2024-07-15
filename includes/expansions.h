/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/09 21:24:55 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
#define EXPANSIONS_H

#include "tokens.h"
#include "a.h"

void	expand(t_Token *token, char *expansion, char *expand_start, char *expand_end);
void	expand_tokens(t_Token_List *tokens, t_entab *env);
char	*copy_var_val(char *key, t_entab *env);
void	tilde_expansion(t_Token_List *tokens, t_entab *env);
void	parameter_expansion(t_Token_List *tokens, t_entab *env);
bool	word_is_quoted(t_Token *token);
void	quote_removal(t_Token_List *tokens);
void	expand_exit_status(t_Token *token, char *dollar);
void	expand_pid(t_Token *token, char *dollar);
void	expand_shname(t_Token *token, char *dollar);
void	expand_variable(t_entab *env, t_Token *token, char *dollar);
bool	is_identifier_character(char c);
bool	is_not_identifier(char c);

#endif
