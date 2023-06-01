/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:52:28 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/01 13:19:28 by sde-smed         ###   ########.fr       */
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
	if (value)
	{
		elem->value = ft_strdup(value);
		if (!elem->value)
		{
			free(elem->name);
			free(elem);
			return (1);
		}
	}
	else
		elem->value = NULL;
	return (0);
}

int	set_env(t_data *data, const char *name, const char *value)
{
	t_env	*elem;

	elem = data->env;
	if (!ft_strcmp(name, "PWD"))
	{
		if (!data->pwd)
			free(data->pwd);
		if (value)
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

char	*get_env(t_env *env, const char *name)
{
	t_env	*elem;

	elem = env;
	while (elem)
	{
		if (!ft_strcmp(elem->name, name))
		{	
			if (elem->value)
				return (ft_strdup(elem->value));
			return (NULL);
		}
		elem = elem->next;
	}
	return (NULL);
}

int	del_env(t_env *env, const char *name)
{
	t_env	*elem;

	elem = find_env_node(env, name);
	if (del_elem(get_previous(env, elem), elem))
		return (1);
	return (0);
}

int	print_env(int fd, t_env *env)
{
	t_env	*elem;

	elem = env;
	while (elem)
	{
		if (elem->value)
		{
			ft_putstr_fd(elem->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(elem->value, fd);
			ft_putstr_fd("\n", fd);
		}
		elem = elem->next;
	}
	return (0);
}
