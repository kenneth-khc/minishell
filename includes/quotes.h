/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:12:11 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/20 22:49:12 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include <stdbool.h>

# define WEAK '"'
# define STRONG '\''

typedef struct s_Quotes
{
	char				quote;
	bool				removal;
	char				*start;
	char				*end;
}	t_Quotes;

typedef struct s_Quote_List
{
	int				pair_count;
	struct s_Quotes	**pairs;
}	t_Quote_List;

typedef struct s_Token	t_Token;

t_Quote_List	find_quotes(t_Token *token);
t_Quotes	*find_next_pair(char *word, char **next_start);
void	store_quotes(t_Quote_List *list, t_Quotes *quotes);
void	print_quote_list(t_Token *token);
void	free_quote_list(t_Quote_List *list);

#endif
