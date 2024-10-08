/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:54:16 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 23:43:34 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_envar			*copy_and_sort_env(t_entab *table);
void			print_and_free_env(t_envar *chead);
static t_envar	*sorted_merge(t_envar *a, t_envar *b);
static void		merge_sort(t_envar **head_ref);
static void		split(t_envar *head, t_envar **front_ref, t_envar **back_ref);

/*chead = copy of head*/
t_envar	*copy_and_sort_env(t_entab *table)
{
	t_envar	*chead;
	t_envar	*node;
	t_envar	*temp;
	t_envar	*prev;

	chead = NULL;
	prev = NULL;
	node = table->head;
	while (node)
	{
		temp = copy_env(node);
		if (chead == NULL)
			chead = temp;
		else
		{
			prev->next = temp;
			temp->prev = prev;
		}
		prev = temp;
		node = node->next;
	}
	merge_sort(&chead);
	return (chead);
}

void	print_and_free_env(t_envar *chead)
{
	t_envar	*node;
	char	*val;

	node = chead;
	while (node)
	{
		if (ft_strcmp("_", node->key) != 0
			&& ((node->state & (DISPLAY | EXPORT)) == (DISPLAY | EXPORT)))
		{
			val = node->val;
			if (val == NULL)
				printf("declare -x %s\n", node->key);
			else if (!node->pwd)
				printf("declare -x %s=\"%s\"\n", node->key, node->val);
			else
				printf("declare -x %s=\"%s\"\n", node->key, node->pwd);
		}
		node = node->next;
	}
	free_env_list(chead);
}

static void	split(t_envar *head, t_envar **front_ref, t_envar **back_ref)
{
	t_envar	*fast;
	t_envar	*slow;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = head;
	*back_ref = slow->next;
	slow->next = NULL;
}

static t_envar	*sorted_merge(t_envar *a, t_envar *b)
{
	t_envar	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (ft_strcmp(a->key, b->key) <= 0)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
		if (result->next != NULL)
			result->next->prev = result;
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
		if (result->next != NULL)
			result->next->prev = result;
	}
	return (result);
}

static void	merge_sort(t_envar **head_ref)
{
	t_envar	*head;
	t_envar	*a;
	t_envar	*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = sorted_merge(a, b);
}
