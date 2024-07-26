/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 18:05:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "env.h"
# include "libft.h"
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

typedef struct s_Range
{
	char	*start;
	char	*end;
}	t_Range;


bool	try_variable_expansion(t_Chunk_List *chunks, t_Quote_List *quote_pairs,
			t_entab *env, t_Range *p);
bool	try_filename_expansion(t_Chunk_List *chunks, t_Token *token, t_Range *p);
bool	delimited(t_Range *p);
bool	is_dollar(char c);

void	point_to_new_chunk(t_Range *p);
bool	do_expansions(t_Token *token, t_entab *env);
bool	check_expansions(t_Range *p, t_Quote_List *quote_pairs, t_entab *env,
			t_Chunk_List *chunks);
void	expand_tokens(t_Token_List *tokens, t_entab *env);
void	tilde_expansion(t_Token *token, t_entab *env);
void	word_splitting(t_Token *token, t_Token_List *tokens);
bool	is_valid_key_start(char *dollar);
bool	parameter_expand(t_Token *token, t_entab *env);
bool	do_variable_expansion(t_Chunk_List *chunks, t_entab *env, t_Range *p);
void	free_chunks(t_Chunk_List *chunks);
size_t	count_total_chunk_len(t_Chunk_List *chunks);
bool	quote_to_remove(t_Quote_List *quote_list, char *quote);
bool	filename_expansion(t_Chunk_List *chunks, t_Token *token);
void	add_chunk(t_Chunk_List *chunks, char *str);
char	*join_chunks(t_Chunk_List *chunks);
char	*copy_var_val(char *key, t_entab *env);
void	quote_removal(t_Token_List *tokens);
void	word_splitting(t_Token *token, t_Token_List *tokens);

char	**match_expression(char *str);
void	unmatch(t_list **list, char *pattern);
char	**list_to_string(t_list *node, char *str);
#endif
