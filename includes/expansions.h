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


bool	check_expansions(t_Range *p, t_Quote_List *quote_pairs, t_entab *env,
			t_Chunk_List *chunks);
bool	dollar_prefix_string(char *dollar, t_Quote_List *quote_list);
bool	should_expand(char *dollar, t_Quote_List *quote_list);
void	expand(t_Token *token, char *expansion,
			char *expand_start, char *expand_end);
void	expand_tokens(t_Token_List *tokens, t_entab *env);
bool	special_parameter(char *dollar);
void	expand_special_parameters(t_Chunk_List *chunks, char *dollar);
void	tilde_expansion(t_Token *token, t_entab *env);
void	word_splitting(t_Token *token, t_Token_List *tokens);
bool	is_valid_key_start(char *dollar);
bool	parameter_expand(t_Token *token, t_entab *env);
void	chunkify_unexpanded_portion(t_Chunk_List *chunks, t_Range *p);
bool	chunkify_expansions(t_Chunk_List *chunks, t_entab *env, t_Range *p);
void	free_chunks(t_Chunk_List *chunks);
size_t	count_total_chunk_len(t_Chunk_List *chunks);
bool	quote_to_remove(t_Quote_List *quote_list, char *quote);
void	filename_expansion(t_Token_List *tokens, t_Token *token, t_entab *env);
void	add_chunk(t_Chunk_List *chunks, char *str);
void	expand_parameter(t_Chunk_List *chunks, t_entab *env, char *dollar);
char	*join_chunks(t_Chunk_List *chunks);
char	*copy_var_val(char *key, t_entab *env);
void	quote_removal(t_Token_List *tokens);
void	word_splitting(t_Token *token, t_Token_List *tokens);

char	**match_expression(char *str);
void	unmatch(t_list **list, char *pattern);
char	**list_to_string(t_list *node, char *str);
#endif
