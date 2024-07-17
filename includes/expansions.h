/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 05:42:32 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "env.h"
# include "tokens.h"
# include <stdbool.h>

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
bool	special_parameter(char *dollar);
void	expand_special_parameters(t_Chunk_List *chunks, char *dollar);
void	tilde_expansion(t_Token *token, t_entab *env);
void	word_splitting(t_Token *token);
bool	is_valid_key_start(char *dollar);
bool	parameter_expand(t_Token *token, t_entab *env);
void	chunkify_unexpanded_portion(t_Chunk_List *chunks, char **start, char **end);
void	chunkify_expansions(t_Chunk_List *chunks, t_entab *env, char **start, char **end);
bool	quote_to_remove(t_Quote_List *quote_list, char *quote);
void	add_chunk(t_Chunk_List *chunks, char *str);
void	expand_parameter(t_Chunk_List *chunks, t_entab *env, char *dollar);
char	*join_chunks(t_Chunk_List *chunks);
char	*copy_var_val(char *key, t_entab *env);
bool	word_is_quoted(t_Token *token);
void	quote_removal(t_Token_List *tokens);
bool	is_identifier_character(char c);
bool	is_not_identifier(char c);

#endif
