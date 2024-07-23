/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:04:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/23 11:42:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "tokens.h"
#include "env.h"
#include "libft.h"
#include "expansions.h"

bool	is_quoted(t_Quote_List *quote_list, char *c)
{
	int			i;
	t_Quotes	*pair;

	i = 0;
	while (i < quote_list->pair_count)
	{
		pair = quote_list->pairs[i];
		if (c > pair->start && c < pair->end)
			return (true);
		i++;
	}
	return (false);
}

// char	*expand_asterisk(char *path, t_entab *table)
// {
// 	DIR				*dir;
// 	char			*ret;
// 	char			*temp;
// 	struct dirent	*entry;
//
// 	temp = ft_strrchr(path, '/');
// 	if (temp == NULL)
// 		temp = ft_strdup(get_var("PWD", table)->val);
// 	else
// 		temp = ft_substr(path, 0, temp - path);
// 	dir = opendir(temp);
// 	if (dir == NULL)
// 		return (NULL);
// 	free(temp);
// 	ret = ft_strdup("");
// 	entry = readdir(dir);
// 	while (entry != NULL)
// 	{
// 		temp = ret;
// 		ret = ft_strjoin(ret, entry->d_name);
// 		free(temp);
// 		entry = readdir(dir);
// 		if (entry != NULL)
// 			ret = ft_strjoin(ret, " ");
// 	}
// 	closedir(dir);
// 	return (ret);
// }

// void	filename_expansion(t_Token_List *tokens, t_Token *token, t_entab *env)
// {(void)tokens;(void)token;(void)env;
// 	printf("|%s|\n", token->lexeme);
// 	// do something i guess
// 	//
// 	char	*asterisk;
//
// 	asterisk = ft_strchr(token->lexeme, '*');
// 	if (asterisk == NULL || is_quoted(&token->quotes, asterisk))
// 		return ;
// 	(void)env;
// 	(void)tokens;
// 	// token->lexeme = expand_asterisk(token->lexeme, env);
// 	// token->type = WORD;
// 	// word_splitting(token, tokens);
// 	char	**words = match_expression(token->lexeme);
// 	char	**w = words;
// 	//t_Token_List	new_tokens;
//
// 	while (*words)
// 	{
// 		printf("|%s|\n", *words);
// 		words++;
// 	}
// 	free(w);
// }
