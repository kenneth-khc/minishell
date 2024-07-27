/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:12:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/28 06:29:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include <stdbool.h>

# define WEAK '"'
# define STRONG '\''

/**
 * A struct representing a pair of quotes.
 * Stores the actual quote character (whether it is ' or ")
 * and the address of the starting and ending quotes
 * Used for quote removal and to check whether an expansion should occur
 **/
typedef struct s_Quotes
{
	char	quote;
	char	*start;
	char	*end;
}	t_Quotes;

/**
 * Stores an array of all the pairs of quotes in a word
 **/
typedef struct s_Quote_List
{
	int				pair_count;
	struct s_Quotes	**pairs;
}	t_Quote_List;

typedef struct s_Token	t_Token;

bool			is_quoted(t_Quote_List *quote_list, char *c);
t_Quote_List	find_quotes(t_Token *token);
t_Quotes		*find_next_pair(char *word, char **next_start);
void			store_quotes(t_Quote_List *list, t_Quotes *quotes);
bool			quote_to_remove(t_Quote_List *quote_list, char *quote);
void			print_quote_list(t_Token *token);
void			free_quote_list(t_Quote_List *list);

#endif
