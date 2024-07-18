/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:04:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 15:52:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "tokens.h"
#include "env.h"
#include "libft.h"

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

char	*expand_asterisk(char *path, t_entab *table)
{
	DIR				*dir;
	char			*ret;
	char			*temp;
	struct dirent	*entry;

	temp = ft_strrchr(path, '/');
	if (temp == NULL)
		temp = ft_strdup(get_var("PWD", table)->val);
	else
		temp = ft_substr(path, 0, temp - path);
	dir = opendir(temp);
	if (dir == NULL)
		return (NULL);
	free(temp);
	ret = ft_strdup("");
	entry = readdir(dir);
	while (entry != NULL)
	{
		temp = ret;
		ret = ft_strjoin(ret, entry->d_name);
		free(temp);
		entry = readdir(dir);
		if (entry != NULL)
			ret = ft_strjoin(ret, " ");
	}
	closedir(dir);
	return (ret);
}

#include <stdio.h>

void	filename_expansion(t_Token *token, t_entab *env)
{
	char	*asterisk;

	asterisk = ft_strchr(token->lexeme, '*');
	if (asterisk == NULL || is_quoted(&token->quotes, asterisk))
		return ;
	printf(">>> %s\n", expand_asterisk((char *)token->lexeme, env));
}
