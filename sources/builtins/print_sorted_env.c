#include "a.h"

void	mergeSort(t_envar **head_ref);

/*chead = copy of head*/
t_envar	*print_sorted_env(t_entab *table)
{
	t_envar	*chead;
	t_envar	*node;
	t_envar	*temp;
	t_envar	*prev;
	char	*val;

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
	mergeSort(&chead);
	node = chead;
  while (node)
	{
    if (ft_strcmp("_", node->key) != 0 && node->display == true)
		{
			val = node->val;
			if (val == NULL)
				printf("declare -x %s\n", node->key);
			else
				printf("declare -x %s=\"%s\"\n", node->key, node->val);
		}
		temp = node->next;
		free(node->key);
		if (node->val)
			free(node->val);
		free(node);
		node = temp;
	}
	return (NULL);
}

void split(t_envar* head, t_envar** front_ref, t_envar** back_ref)
{
	t_envar* fast;
	t_envar* slow;
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

t_envar* sortedMerge(t_envar* a, t_envar* b)
{
  t_envar*	result;

	result = NULL;
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
  if (ft_strcmp(a->key, b->key) <= 0)
	{
		result = a;
		result->next = sortedMerge(a->next, b);
		if (result->next != NULL)
			result->next->prev = result;
	} 
	else
	{
		result = b;
		result->next = sortedMerge(a, b->next);
		if (result->next != NULL)
			result->next->prev = result;
	}
	return (result);
}

void mergeSort(t_envar** head_ref)
{
	t_envar*	head;
	t_envar*	a;
	t_envar*	b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL)) {
		return ;
	}
	split(head, &a, &b);
	mergeSort(&a);
	mergeSort(&b);
	*head_ref = sortedMerge(a, b);
}
