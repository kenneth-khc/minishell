/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:53:19 by qang              #+#    #+#             */
/*   Updated: 2024/07/19 22:48:41 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>

char	**match_expression(char *str);
static void  fill_list(t_list **node, DIR *dir, char *expr, char *path);
static void  recursive_fill(t_list **node, char *str, char *path);

static void  fill_list(t_list **node, DIR *dir, char *expr, char *path)
{
	struct dirent *entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (expr[0] == '.' && entry->d_name[0] == '.')
			ft_lstadd_back(node, ft_lstnew(ft_strjoin(path, entry->d_name)));
		else if (expr[0] != '.'&& entry->d_name[0] != '.')
			ft_lstadd_back(node, ft_lstnew(ft_strjoin(path, entry->d_name)));
		entry = readdir(dir);
	}
}

static void  recursive_fill(t_list **node, char *str, char *path)
{
	char  *temp;
	char	*expr;
	DIR   *dir;
	struct dirent *entry;

	temp = ft_strchr(str, '/');
	if (!temp)
	{
		if (ft_strlen(path) == 0)
			dir = opendir(".");
		else
			dir = opendir(path);
		if (dir)
		{
			expr = ft_strjoin(path, "/");
			fill_list(node, dir, str, expr);
			closedir(dir);
		}
	}
	else
	{
		if (ft_strlen(path) == 0)
			dir = opendir(".");
		else
			dir = opendir(path);
		if (dir)
		{
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (ft_strcmp(entry->d_name, ".") == 0)
				{
					entry = readdir(dir);
					continue ;
				}
				if (ft_strcmp(path, "..") == 0)
					expr = ft_strjoin(ft_strjoin(path, "/"), entry->d_name);
				else
					expr = ft_strjoin(path, entry->d_name);
				recursive_fill(node, temp + 1, expr);
				entry = readdir(dir);
			}
			closedir(dir);
		}
	}
}

char	**match_expression(char *str)
{
	t_list	*node;

	node = NULL;
	recursive_fill(&node, str, "");
	unmatch(&node, str);
	return (list_to_string(node, str));
}
