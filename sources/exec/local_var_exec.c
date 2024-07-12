/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:10:26 by qang              #+#    #+#             */
/*   Updated: 2024/07/12 01:59:19 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"
#include "tree.h"

void	*mallocpromax(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_dprintf(2, "error: malloc failed\n");
		exit(1);
	}
	return (ptr);
}

static t_entab	*create_local_table(t_envar *node, char **var)
{
	t_entab	*table;
	t_envar	*temp;
	int		i;

	table = mallocpromax(sizeof(t_entab));
	temp = copy_env(node);
	table->head = temp;
	while (temp)
	{
		table->tail = temp;
		temp = temp->next;
	}
	i = 0;
	while (var[i])
		add_var(var[i++], table);
	return (table);
}

void  local_var_exec(t_Exec_Node *node, char **var)
{
	t_entab	*table;
	int		pid;
	char	*file_path;

	pid = forkpromax();
	if (pid == 0)
	{
		table = create_local_table(node->table->head, var);
		file_path = (char *)node->command;
		if (access(file_path, F_OK) == 0 && access(file_path, X_OK) == 0)
			execve(file_path, (char **)node->args, env_convert(table));
		execvepromax((char **)node->args, table, get_var("PATH", table));
		ft_dprintf(2, "%s: command not found\n", SHELL, node->command);
		exit(127);
	}
	wait_for_child(pid);
}