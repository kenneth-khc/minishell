/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:14:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/05 09:25:11 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "tokens.h"
#include <stdio.h>

char
**split_expansion(t_Expansion *expansion, t_Token_List *new_list);

/*
static bool
expansions_double_quoted(t_Expansion *expansion, t_Quote_List *quotes);
*/

void	
print_chunks(t_Chunk_List *chunks);

void	word_split(t_Expansion_List *expansions,
					t_Token_List *tokens, t_Token *token)
{
	(void)tokens;
	(void)token;
	if (expansions->head == NULL)
		return ;
}
/*
	t_Chunk_List	chunks;
	t_Expansion		*expansion;
	char			*s;
	t_Token_List	new_words;
	char			**words;

	chunks = (t_Chunk_List){.head = NULL, .tail = NULL};
	new_words = (t_Token_List){.head = NULL, .tail = NULL};
	expansion = expansions->head;
	s = token->lex->start;
	while (expansion)
	{
		if (!expansions_double_quoted(expansion, &token->quotes)
			&& expansion->start >= token->lex->start
			&& expansion->end <= token->lex->end)
		{
			add_chunk(&chunks, ft_extract_substring(s, expansion->start - 1));
			words = split_expansion(expansion, &new_words);
			while (words && *words)
			{
				printf("T:|%s|\n", *words);
				add_chunk(&chunks, *words);
				words++;
			}
		}
		expansion = expansion->next;
	}
	(void)tokens;
	print_chunks(&chunks);
*/

char	**split_expansion(t_Expansion *expansion, t_Token_List *new_list)
{
	t_String	*str;
	char		**splitted;
	t_Token		*new_token;
	t_Token		*temp;

	str = string_extract(expansion->start, expansion->end);
	printf(">>>|%s|\n", str->start);
	splitted = ft_split(str->start, ' ');
	while (*splitted)
	{
		new_token = create_token(WORD, *splitted);
		add_token(new_list, new_token);
		splitted++;
	}
	temp = new_list->head;
	while (temp)
	{
		printf("Tok: |%s|\n", temp->lexeme);
		temp = temp->next;
	}
	return (splitted);
}

/*
static bool	expansions_double_quoted(t_Expansion *expansion,
									t_Quote_List *quotes)
{
	int			i;
	t_Quotes	*quote;

	i = 0;
	while (i < quotes->pair_count)
	{
		quote = quotes->pairs[i];
		if (quote->quote == '"'
			&& quote->start > expansion->start
			&& expansion->end < quote->end)
			return (true);
		i++;
	}
	return (false);
}
*/
