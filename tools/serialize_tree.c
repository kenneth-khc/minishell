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
#include <stdlib.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "tree.h"
#include "cJSON.h"

static char	*get_data(t_Node *node)
{
	char			*str;
	t_Exec_Node		*e;
	t_Redir_Node	*r;
	t_Ass_Node		*a;

	if (node == NULL)
		return (NULL);
	str = NULL;
	if (node->type == Exec_Node)
	{
		e = (t_Exec_Node *)node;
		char *cmd = (char *)e->command;
		char *args[10] = {NULL};
		str = ft_strjoin(cmd, "\n");
		for (int i = 0; i < e->arg_count; i++)
		{
			if (i == 0)
				continue ;
			args[i] = (char *)e->args[i];
			str = ft_strjoin(str, args[i]);
			str = ft_strjoin(str, " ");
		}
	}
	else if (node->type == Pipe_Node)
		str = "PIPE";
	else if (node->type == Redir_Node)
	{
		r = (t_Redir_Node *)node;
		char *old = ft_itoa(r->oldfd);
		char *op;
		if (r->mode == 0)
			op = "<";
		else if (r->flags & O_TRUNC)
			op = ">";
		else if (r->flags & O_APPEND)
			op = ">>";
		else
			op = "???";
		char *new = (char *)r->file;
		str = ft_strjoin_multiple(3, old, op, new);

	}
	else if (node->type == AND_AND_NODE)
		str = "&&";
	else if (node->type == OR_OR_NODE)
		str = "||";
	else if (node->type == ASS_NODE)
	{
		a = (t_Ass_Node *)node;
	printf("loool\n");
		str = ft_strjoin_multiple(3, a->key, "=", a->value);
	}
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
	char	*temp = get_data(node);
	data = cJSON_CreateString(temp);
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
	printf("%s\n", json_str);
	ft_dprintf(fd, "%s", json_str);
	free(json_str);
	cJSON_Delete(tree);
//	system("python3 visualize.py");
}
