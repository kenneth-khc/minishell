/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:27:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/07 03:02:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "tokens.h"
#include "expansions.h"

static void
update_token_chain(t_Token_List *tokens, t_Token_List *filenames,
	t_Token *token);

void	filename_expansion(t_Token *token, t_Token_List *tokens)
{
	char			**files;
	char			**ff;
	t_Token_List	filenames;

	if (ft_strchr(token->lex->start, '*') == NULL)
		return ;
	files = match_expression(token->lex->start);
	if (ft_strcmp(*files, token->lex->start) == 0)
		return ;
	filenames = (t_Token_List){.head = NULL, .tail = NULL};
	ff = files;
	while (*files)
	{
		add_token(&filenames, create_token(WORD, *files));
		files++;
	}
	free(ff);
	update_token_chain(tokens, &filenames, token);
	return ;
}

static void	update_token_chain(t_Token_List *tokens, t_Token_List *filenames,
								t_Token *token)
{
	t_Token	*temp;

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
	temp = token;
	token = filenames->head;
	free_quote_list(&temp->quotes);
	string_free(temp->lex);
}
