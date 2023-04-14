/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:15:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/14 12:40:47 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Copies a linked list of environment variables.
** @param head the head of the linked list to copy
** @return a pointer to the head of the new linked list
*/
static t_env	*copy_env_list(t_env *head)
{
	t_env	*new_head;
	t_env	*tail;
	t_env	*new_node;

	new_head = NULL;
	tail = NULL;
	while (head != NULL)
	{
		new_node = malloc(sizeof(t_env));
		new_node->var = ft_strdup(head->var);
		new_node->next = NULL;
		if (tail == NULL)
		{
			new_head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		head = head->next;
	}
	return (new_head);
}

/*
** Swaps the values of two environment variables.
** @param a the first variable to swap
** @param b the second variable to swap
** @return void
*/
void	swap(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->var;
	a->var = b->var;
	b->var = tmp;
}

/*
** Sorts a linked list of environment variables in ascending order.
** @param head a pointer to the head of the linked list to sort
** @return void
*/
void	sort_list(t_env **head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	if (*head == NULL)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->var, ptr1->next->var) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

/*
** Prints the values of all exportable environment variables
** in the specified format.
** @param old_head a pointer to the head of the linked list
** of environment variables
** @return 0 if successful, 1 otherwise
*/
int	export_print(t_env *old_head)
{
	t_env	*head;

	head = copy_env_list(old_head);
	sort_list(&head);
	while (head != NULL)
	{
		printf("declare -x %s\n", head->var);
		head = head->next;
	}
	ft_envclear(&head);
	return (0);
}
