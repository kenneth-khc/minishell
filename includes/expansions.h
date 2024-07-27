/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 06:25:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <stdbool.h>
# include "env.h"
# include "libft.h"
# include "tokens.h"

// Chunks for storing untouched and expanded sections of the word,
// then joining them back together
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

void	add_chunk(t_Chunk_List *chunks, char *str);
void	point_to_new_chunk(t_Range *p);
size_t	count_total_chunk_len(t_Chunk_List *chunks);
char	*join_chunks(t_Chunk_List *chunks);
void	free_chunks(t_Chunk_List *chunks);

void	expand_tokens(t_Token_List *tokens, t_entab *env);
bool	do_expansions(t_Token *token, t_entab *env);
void	tilde_expansion(t_Token *token, t_entab *env);
bool	try_variable_expansion(t_Chunk_List *chunks,
			t_Quote_List *quote_pairs, t_entab *env, t_Range *p);
bool	do_variable_expansion(t_Chunk_List *chunks, t_entab *env, t_Range *p);
bool	try_filename_expansion(t_Chunk_List *chunks,
			t_Token *token, t_Range *p);
bool	filename_expansion(t_Chunk_List *chunks, t_Token *token);
char	**match_expression(char *str);
void	unmatch(t_list **list, char *pattern);
char	**list_to_string(t_list *node, char *str);
void	word_splitting(t_Token *token, t_Token_List *tokens);
bool	delimited(t_Range *p);
bool	is_dollar(char c);
bool	is_valid_key_start(char *dollar);
char	*copy_var_val(char *key, t_entab *env);

#endif
