/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:18:18 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:23:01 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

int	unset(char **args, t_entab *table);

int	unset(char **args, t_entab *table)
{
	int		i;
	char	*new;
	char	*temp;
	t_envar	*node;

	i = 0;
	while (args[++i])
	{
		node = get_var(args[i], table);
		if (node == NULL)
			continue ;
		temp = ft_strjoin(node->key, "=");
		if (node->val)
		{
			new = ft_strjoin(temp, node->val);
			free(temp);
		}
		else
			new = temp;
		del_var(args[i], table);
		add_var(new, table);
		table->tail->state &= ~(DISPLAY | EXPORT);
		free(new);
	}
	return (0);
}
