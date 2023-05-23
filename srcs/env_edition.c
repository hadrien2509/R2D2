/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:25:54 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/23 14:03:44 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Clears the linked list containing environment variables.
** @param lst the address of a pointer to the first node of the list
*/
void	ft_envclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

int	allocate_memory(t_env *new, const char *name, const char *value)
{
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (0);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (0);
		}
	}
	else
		new->value = NULL;
	return (1);
}

t_env	*ft_envnew(const char *name, const char *value)
{
	t_env	*new;

	if (!name)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!allocate_memory(new, name, value))
		return (NULL);
	new->next = NULL;
	return (new);
}

/*
** Adds a new environment variable node at the end of a linked list.
** @param list the address of a pointer to the first node of the list,
** or NULL if the list is empty
** @param new a pointer to the new node to add
*/
void	ft_envadd_back(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

/*
** Deletes the given node in a linked list and frees its memory.
** @param prev the previous node of the node to be deleted,
** NULL if the node to be deleted is the head
** @param to_del the node to be deleted
** @return 0 if successful, 1 if the node to be deleted is NULL
*/
int	del_elem(t_env *prev, t_env *to_del)
{
	if (to_del == NULL)
		return (1);
	if (prev == NULL)
	{
		free(to_del->name);
		free(to_del->value);
		free(to_del);
		return (0);
	}
	prev->next = to_del->next;
	free(to_del->name);
	free(to_del->value);
	free(to_del);
	return (0);
}
