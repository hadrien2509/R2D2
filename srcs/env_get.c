/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:19:41 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/16 22:34:53 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Searches for the node with the given variable name in a linked list.
** @param env the linked list to search in
** @param arg the variable name to search for
** @return the node containing the variable name, NULL if not found
*/
t_env	*find_env_node(t_env *env, const char *name)
{
	t_env	*current;

	if (env == NULL || name == NULL)
		return (NULL);
	current = env;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, name))
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

/*
** Initializes the data struct with a newly created linked list of environment
** variables from a null-terminated string array.
** @param data a pointer to the data struct to initialize
** @param env the null-terminated string array to copy from
** @return 0 if successful, -1 if the allocation fails
*/
int	init_data(t_data *data, char **env)
{
	int		shell_lvl;
	char	*shlvl;

	shell_lvl = 0;
	data->exit_status = 0;
	data->env = ft_strarr_to_env(data, env);
	if (!data->env)
		return (1);
	set_env(data, "OLDPWD", NULL);
	shlvl = get_env(data->env, "SHLVL");
	if (shlvl)
		shell_lvl = ft_atoi(shlvl);
	if (shell_lvl < 0)
		set_env(data, "SHLVL", "0");
	else
		set_env(data, "SHLVL", ft_itoa(++shell_lvl));
	data->pwd = get_env(data->env, "PWD");
	if (!data->pwd)
		return (1);
	return (0);
}
