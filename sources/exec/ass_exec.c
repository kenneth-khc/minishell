/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:26:55 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 12:10:13 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

void	ass_var(t_Ass_Node *node);

void	ass_var(t_Ass_Node *node)
{
	char	*temp;
	char	*temp1;

	if (node->value == NULL)
		return ;
	temp = ft_strjoin(node->key, "=");
	temp1 = ft_strjoin(temp, node->value);
	add_ass(temp1, node->table);
	free(temp);
	free(temp1);
	exec_ast(node->left);
}
