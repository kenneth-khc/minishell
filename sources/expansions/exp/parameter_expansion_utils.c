/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:36:18 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/03 18:47:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "definitions.h"

bool	is_expansion(char *c, t_Quote_List *quotes)
{
	int			i;
	t_Quotes	*pair;

	if (*c != '$')
		return (false);
	i = 0;
	while (i < quotes->pair_count)
	{
		pair = quotes->pairs[i];
		if (c > pair->start
			&& c < pair->end)
		{
			if (pair->quote == STRONG)
				return (false);
			else if (pair->quote == WEAK)
				return (true);
		}
		i++;
	}
	return (true);
}

size_t	calculate_expanded_len(t_Expansion_List *expansions)
{
	size_t		len;
	t_Expansion	*expansion;

	len = 0;
	expansion = expansions->head;
	while (expansion)
	{
		len += expansion->value->len;
		expansion = expansion->next;
	}
	return (len);
}

size_t	calculate_unexpanded_len(t_Token *token, t_String *lexeme)
{
	size_t	len;
	char	*p;
	bool	expansion_found;

	len = 0;
	p = lexeme->start;
	expansion_found = false;
	while (p < lexeme->end)
	{
		if (!expansion_found && is_expansion(p, &token->quotes))
		{
			expansion_found = true;
			if (is_identifier_start(p))
			{
				p = ft_strpbrk(p + 1, is_not_identifier);
				continue ;
			}
		}
		len++;
		p++;
	}
	return (len);
}

