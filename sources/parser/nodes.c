/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:09:48 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/06 09:27:32 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "tokens.h"
#include "tree.h"

/**
 * Construct a node for redirection
 * A pointer to the environment is stored for execution
**/
t_Redir_Node	*redir_node(t_entab *env)
{
	t_Redir_Node	*redir;

	redir = callocpromax(1, sizeof(*redir));
	redir->type = REDIR_NODE;
	redir->table = env;
	return (redir);
}

/**
 * Construct a node for assignment
 * A pointer to the env is stored for updating the table with the ass
 * If value is empty, the variable is set to an empty string (not NULL)
**/
t_Node	*assignment_node(t_Token *token, t_entab *env)
{
	t_Ass_Node	*ass;
	const char	*equal;
	const char	*end;

	ass = callocpromax(1, sizeof(*ass));
	equal = ft_strchr(token->lex->start, '=');
	ass->type = ASS_NODE;
	ass->key = ft_extract_substring(token->lex->start, equal - 1);
	end = token->lex->end;
	if (equal[1] == '\0')
		ass->value = "";
	else
		ass->value = ft_extract_substring(equal + 1, end);
	ass->table = env;
	ass->left = NULL;
	return ((t_Node *)ass);
}
