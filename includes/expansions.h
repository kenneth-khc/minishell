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

typedef struct s_Chunk
{
	char			*str;
	struct s_Chunk	*next;
}	t_Chunk;

typedef struct s_Chunk_List
{
	struct s_Chunk	*head;
	struct s_Chunk	*tail;
}	t_Chunk_List;

bool	should_expand(char *dollar, t_Quote_List *quote_list);
void	expand(t_Token *token, char *expansion, char *expand_start, char *expand_end);
bool	only_digits(const char *str);
void	io_number(t_Token *token);
void	expand_tokens(t_Token_List *tokens, t_entab *env);
void	tilde_expansion(t_Token *token, t_entab *env);
void	parameter_expand(t_Token *token, t_entab *env);
bool	quote_to_remove(t_Quote_List *quote_list, char *quote);
void	add_chunk(t_Chunk_List *chunks, char *str);
void	expand_into_chunk_list(t_Chunk_List *chunks, t_entab *env, char *dollar);
char	*join_chunks(t_Chunk_List *chunks);
char	*copy_var_val(char *key, t_entab *env);
bool	word_is_quoted(t_Token *token);
void	quote_removal(t_Token_List *tokens);
bool	is_identifier_character(char c);
bool	is_not_identifier(char c);

#endif
