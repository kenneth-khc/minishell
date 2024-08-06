/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:47 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:58:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <stdbool.h>
# include "env.h"
# include "libft.h"
# include "ft_string.h"
# include "tokens.h"

# define GET 0
# define RESET 1

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

bool		is_expansion(char *c, t_Quote_List *quotes);
bool		in_expansions(t_Expansion_List *expansions, char *c);
void		expand_tokens(t_Token_List *tokens, t_entab *env);

t_Expansion	*create_expansion(t_String *key, t_String *value, size_t offset);
void		add_expansion(t_Expansion_List *expansions, t_Expansion *expansion);
t_Expansion	*get_next_expansion(t_Expansion_List *expansions, bool reset);
void		clear_expansion_list(t_Expansion_List *expansions);

/* Expanding tilde into HOME */
void		tilde_expansion(t_Expansion_List *expansions, t_Token *token,
				t_entab *env);

/* Expanding local and environment variables */
void		parameter_expansion(t_Expansion_List *expansions, t_Token *token,
				t_entab *env);
void		expand_string(t_Expansion_List *expansions, t_Token *token,
				char *dollar);
void		expand_variable(t_Expansion_List *expansions, t_Token *token,
				char *dollar, t_entab *env);
void		expand_special_parameter(t_Expansion_List *expansions,
				t_Token *token, char *dollar);

void		update_token_lexeme(t_Token *token, t_Expansion_List *expansions);

/* Expanding asterisks into filenames */
void		filename_expansion(t_Token *token, t_Token_List *tokens);
char		**match_expression(char *str);
void		unmatch(t_list **list, char *pattern);
char		**list_to_string(t_list *node, char *str);

/* Removing unquoted quotes from the input */
void		quote_removal(t_Token *token);

/**
 * Original implementation of expansions was to do a single pass through the
 * word, expanding variables into a separate buffer as it sees them,
 * skips over quotes that needs to be removed, then all the resulting chunks
 * back to form the final word. However, this caused problems as everything is
 * done out of order not following the standards.
 */

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

/* Helper struct for storing 2 character addresses, range is a bad name */
typedef struct s_Range
{
	char	*start;
	char	*end;
}	t_Range;

void		add_chunk(t_Chunk_List *chunks, char *str);
void		point_to_new_chunk(t_Range *p);
size_t		count_total_chunk_len(t_Chunk_List *chunks);
char		*join_chunks(t_Chunk_List *chunks);
void		free_chunks(t_Chunk_List *chunks);

#endif
