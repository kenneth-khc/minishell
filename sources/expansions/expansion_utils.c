/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:57:21 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 02:57:40 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/**
* Create a new structure storing the metadata of an expansion in a word
* offset tracks where the expansion begins relative to the start of the word
*/
t_Expansion	*create_expansion(t_String *key, t_String *value, size_t offset)
{
	t_Expansion	*new_expansion;

	new_expansion = malloc(sizeof(*new_expansion));
	new_expansion->key = key;
	new_expansion->value = value;
	if (value == NULL)
		offset = -1;
	else
		new_expansion->offset = offset;
	new_expansion->start = NULL;
	new_expansion->end = NULL;
	new_expansion->next = NULL;
	return (new_expansion);
}

void	add_expansion(t_Expansion_List *expansions, t_Expansion *expansion)
{
	if (expansions->head == NULL)
		expansions->head = expansion;
	if (expansions->tail)
		expansions->tail->next = expansion;
	expansions->tail = expansion;
}

void	clear_expansion_list(t_Expansion_List *expansions)
{
	t_Expansion	*expansion;

	expansion = expansions->head;
	while (expansion)
	{
		string_free(expansion->key);
		string_free(expansion->value);
		free(expansion);
		expansion = expansion->next;
	}
	expansions->head = NULL;
	expansions->tail = NULL;
	get_next_expansion(NULL, RESET);
}
