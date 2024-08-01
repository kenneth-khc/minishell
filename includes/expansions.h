/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/03 13:23:15 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <stdbool.h>
# include "env.h"
# include "libft.h"
# include "ft_string.h"
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

typedef struct s_Expansion
{
	char				*start;
	char				*end;
	t_String			*key; // the original key, including the $ character
	t_String			*value; // the value of the variable
	ssize_t				offset; // offset relative to the start of the word
	struct s_Expansion	*next;
}	t_Expansion;

typedef struct s_Expansion_List
{
	struct s_Expansion	*head;
	struct s_Expansion	*tail;
}	t_Expansion_List;

void	add_chunk(t_Chunk_List *chunks, char *str);
void	point_to_new_chunk(t_Range *p);
size_t	count_total_chunk_len(t_Chunk_List *chunks);
char	*join_chunks(t_Chunk_List *chunks);
void	free_chunks(t_Chunk_List *chunks);

void	expand_tokens(t_Token_List *tokens, t_entab *env);
bool	do_expansions(t_Token *token, t_entab *env);
/*void	tilde_expansion(t_Token *token, t_entab *env);*/
void	tilde_expansion(t_Expansion_List *expansions, t_Token *token, t_entab *env);
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
bool	is_identifier_start(char *dollar);
char	*copy_var_val(char *key, t_entab *env);

bool	variable_should_expand(char *dollar, t_Quote_List *quote_list);

bool	is_expansion(char *c, t_Quote_List *quotes);
void	add_expansion(t_Expansion_List *expansions, t_Expansion *expansion);
t_Expansion	*get_next_expansion(t_Expansion_List *expansions, bool reset);
void	parameter_expansion(t_Expansion_List *expansions, t_Token *token, t_entab *env);
t_Expansion	*create_expansion(t_String *key, t_String *value, size_t offset);
void	update_token_lexeme(t_Token *token, t_Expansion_List *expansions, t_Range *p);
size_t			calculate_expanded_len(t_Expansion_List *expansions);
size_t			calculate_unexpanded_len(t_Token *token, t_String *lexeme);
t_Quote_List	find_quoted_sections(t_Token *token, t_Expansion_List *expansions);
void	word_split(t_Expansion_List *expansions, t_Token *token);

#endif
