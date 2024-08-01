/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:27:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/05 10:04:55 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "tokens.h"
#include "expansions.h"

/*
static void	add_spaces_between_chunks(t_Chunk_List *chunks);
*/

static void
update_token_chain(t_Token_List *tokens, t_Token_List *filenames,
	t_Token *token);

bool	filename_expand(t_Token *token, t_Token_List *tokens)
{
	char			**files;
	char			**ff;
	t_Token_List	filenames;

	files = match_expression(token->lexeme);
	if (ft_strcmp(*files, token->lexeme) == 0)
		return (false);
	filenames = (t_Token_List){.head = NULL, .tail = NULL};
	ff = files;
	while (*files)
	{
		add_token(&filenames, create_token(WORD, *files));
		files++;
	}
	free(ff);
	update_token_chain(tokens, &filenames, token);
	return (true);
}

static void	update_token_chain(t_Token_List *tokens, t_Token_List *filenames,
								t_Token *token)
{
	if (token->prev)
		token->prev->next = filenames->head;
	else
		tokens->head = filenames->head;
	if (token->next)
		token->next->prev = filenames->tail;
	else
		tokens->tail = filenames->tail;
	filenames->head->prev = token->prev;
	filenames->tail->next = token->next;
	token = filenames->head;
}

/*
static void	add_spaces_between_chunks(t_Chunk_List *chunks)
{
	t_Chunk	*chunk;
	t_Chunk	*space;

	chunk = chunks->head;
	while (chunk->next)
	{
		space = callocpromax(1, sizeof(*space));
		space->str = callocpromax(1, sizeof(char));
		space->str[0] = ' ';
		space->next = chunk->next;
		chunk->next = space;
		chunk = space->next;
	}
}
*/
