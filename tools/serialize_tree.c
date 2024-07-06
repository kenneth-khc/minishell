/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:36:23 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/06 17:29:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "tree.h"
#include "cJSON.h"

static char	*get_data(t_Node *node)
{
	char			*str;
	t_Redir_Node	*r;

	if (node == NULL)
		return (NULL);
	str = NULL;
	if (node->type == Exec_Node)
		str = (char *)((t_Exec_Node *)node)->command;
	else if (node->type == Pipe_Node)
		str = "PIPE";
	else if (node->type == Redir_Node)
	{
		r = (t_Redir_Node *)node;
		if (r->oldfd == 0)
			str = ft_strjoin(ft_itoa(r->oldfd), "<");
		else if (r->oldfd == 1)
			str = ft_strjoin(ft_itoa(r->oldfd), ">");
		str = ft_strjoin(str, r->file);
	}
	else if (node->type == AND_AND_NODE)
		str = "&&";
	else if (node->type == OR_OR_NODE)
		str = "||";
	return (str);
}

static cJSON	*node_to_json(t_Node *node)
{
	cJSON	*ret;
	cJSON	*data;
	cJSON	*left;
	cJSON	*right;

	if (node == NULL)
		return (NULL);
	ret = cJSON_CreateObject();
	data = cJSON_CreateString(get_data(node));
	if (data == NULL)
		data = cJSON_CreateString("NULL");
	cJSON_AddItemToObject(ret, "string", data);
	if (node->left)
		left = node_to_json(node->left);
	else
		left = cJSON_CreateNull();
	cJSON_AddItemToObject(ret, "left", left);
	if (node->right)
		right = node_to_json(node->right);
	else
		right = cJSON_CreateNull();
	cJSON_AddItemToObject(ret, "right", right);
	return (ret);
}

void	export_tree(t_Node *node)
{
	int		fd;
	cJSON	*tree;
	char	*json_str;

	fd = open("tree.json", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	tree = node_to_json(node);
	json_str = cJSON_Print(tree);
//	printf("%s\n", json_str);
	ft_dprintf(fd, "%s", json_str);
	free(json_str);
	cJSON_Delete(tree);
//	system("python3 visualize.py");
}
