/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:19:41 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/13 12:25:05 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Searches for the node with the given variable name in a linked list.
** @param env the linked list to search in
** @param arg the variable name to search for
** @return the node containing the variable name, NULL if not found
*/
t_env	*find_env_node(t_env *env, const char *arg)
{
	t_env	*current;

	if (env == NULL || arg == NULL)
		return (NULL);
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, arg) == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*
** Returns the previous node of the given node in a linked list.
** @param env the linked list to search in
** @param current the current node to find the previous node of
** @return the previous node, NULL if the given node is the head or not found
*/
t_env	*get_previous(t_env *env, t_env *current)
{
	t_env	*previous;

	if (env == NULL || current == NULL)
		return (NULL);
	if (env == current)
		return (NULL);
	previous = env;
	while (previous != NULL && previous->next != current)
		previous = previous->next;
	return (previous);
}

/*
** Gets the last node of a linked list.
** @param env a pointer to the first node of the list,
	or NULL if the list is empty
** @return a pointer to the last node of the list, or NULL if the list is empty
*/
t_env	*get_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}
