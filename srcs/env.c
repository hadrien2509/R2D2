/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:52:28 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/27 10:35:57 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_env(t_env *elem, const char *value, const char *name)
{
	if (!value)
		return (0);
	free(elem->name);
	if (elem->value)
		free(elem->value);
	elem->name = ft_strdup(name);
	if (!elem->name)
	{
		free(elem);
		return (1);
	}
	elem->value = ft_strdup(value);
	if (!elem->name)
	{
		free(elem->value);
		free(elem);
		return (1);
	}
	return (0);
}

/*
** Sets a value to an environment variable.
** @param env the environment variables list
** @param name the variable name
** @param value the new value
** @return 0 if successful, 1 otherwise
*/
int	set_env(t_data *data, const char *name, const char *value)
{
	t_env	*elem;

	elem = data->env;
	if (!ft_strcmp(name, "PWD"))
	{
		free(data->pwd);
		data->pwd = ft_strdup(value);
		if (!data->pwd)
			return (42);
	}
	while (elem)
	{
		if (!ft_strcmp(elem->name, name))
			return (update_env(elem, value, name));
		elem = elem->next;
	}
	elem = get_last(data->env);
	ft_envadd_back(&elem, ft_envnew(name, value));
	if (value)
		data->env_size++;
	return (0);
}

/*
** Returns the value of an environment variable.
** @param env the environment variables list
** @param var the variable name
** @return the value of the environment variable, or NULL if it is not found
*/
char	*get_env(t_env *env, const char *name)
{
	t_env	*elem;

	elem = env;
	while (elem)
	{
		if (!ft_strcmp(elem->name, name))
			return (ft_strdup(elem->value));
		elem = elem->next;
	}
	return (NULL);
}

/*
** Deletes an environment variable from the list.
** @param env the environment variables list
** @param var the variable name
** @return 0 if successful, 1 otherwise
*/
int	del_env(t_env *env, const char *name)
{
	t_env	*elem;

	elem = find_env_node(env, name);
	if (del_elem(get_previous(env, elem), elem))
		return (1);
	return (0);
}

/*
** Prints the environment variables.
** @param env the environment variables list
** @return 0 if successful, -1 otherwise
*/
int	print_env(t_env *env)
{
	t_env	*elem;

	elem = env;
	while (elem)
	{
		if (elem->value)
			printf("%s=%s\n", elem->name, elem->value);
		elem = elem->next;
	}
	return (0);
}
