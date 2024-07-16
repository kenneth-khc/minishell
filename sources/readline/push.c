/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:40:53 by qang              #+#    #+#             */
/*   Updated: 2024/07/15 02:02:51 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

#include <stdlib.h>
#include <stdio.h>

void	push(t_history **a, t_history **b)
{
	t_history	*tmp;

	if (!*a)
		return ;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = *b;
	*b = tmp;
}

void	add_history(char *str, t_history **lst)
{
	t_history	*new;

	if (!lst || !str)
		return ;
	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
	{
		printf("Error while allocating memory\n");
		exit(1);
	}
	new->line = str;
	new->next = *lst;
	*lst = new;
}
