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

static char	*exec_to_json(t_Exec_Node *node)
{
	char	*str;
	char	*cmd;
	char	*args[100] = {NULL};
	char	*temp;

	cmd = (char *)node->command;
	str = ft_strjoin(cmd, "\n");
	for (int i = 0; i < node->arg_count; i++)
	{
		if (i == 0)
			continue ;
		args[i] = (char *)node->args[i];
		temp = str;
		str = ft_strjoin_multiple(3, str, args[i], " ");
		free(temp);	
	}
	return (str);
}

static char	*redir_to_json(t_Redir_Node *node)
{
	char	*str;
	char	*old;
	char	*op;
	char	*new;

	old = ft_itoa(node->oldfd);
	if (node->mode == 0)
		op = "<";
	else if (node->heredoc)
	{
		op = " << ";
		str = ft_strjoin_multiple(4, "HEREDOC\n", old, op, node->delim);
		return (str);
	}
	else if (node->flags & O_TRUNC)
		op = " > ";
	else if (node->flags & O_APPEND)
		op = " >> ";
	else
		op = "???";
	new = (char *)node->file;
	str = ft_strjoin_multiple(3, old, op, new);
	free(old);
	return (str);
}

static char	*get_data(t_Node *node)
{
	char			*str;
	t_Ass_Node		*a;

	if (node == NULL)
		return (NULL);
	str = NULL;
	if (node->type ==EXEC_NODE)
		str = exec_to_json((t_Exec_Node *)node);
	else if (node->type ==PIPE_NODE)
		str = "PIPE";
	else if (node->type ==REDIR_NODE)
		str = redir_to_json((t_Redir_Node *)node);
	else if (node->type == AND_AND_NODE)
		str = "&&";
	else if (node->type == OR_OR_NODE)
		str = "||";
	else if (node->type == ASS_NODE)
	{
		a = (t_Ass_Node *)node;
		str = ft_strjoin_multiple(3, a->key, "=", a->value);
	}
	else if (node->type == SUBSHELL_NODE)
		str = "SUBSHELL";
	return (str);
}

static cJSON	*node_to_json(t_Node *node)
{
	cJSON	*ret;
	cJSON	*data;
	cJSON	*left;
	cJSON	*right;
	char	*temp;

	ret = cJSON_CreateObject();
	if (node == NULL)
	{
		cJSON_AddItemToObject(ret, "string", cJSON_CreateString("NULL"));
		return (ret);
	}
	temp = get_data(node);
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

	fd = open("tree.json", O_CREAT | O_WRONLY | O_TRUNC,
		   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	tree = node_to_json(node);
	json_str = cJSON_Print(tree);
//	printf("%s\n", json_str);
	ft_dprintf(fd, "%s", json_str);
	free(json_str);
	cJSON_Delete(tree);
//	system("python3 visualize.py");
}
