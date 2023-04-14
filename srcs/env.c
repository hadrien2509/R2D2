/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:52:28 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/14 14:09:39 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Sets a value to an environment variable.
** @param env the environment variables list
** @param var the variable name
** @param new_val the new value
** @return 0 if successful, 1 otherwise
*/
int	set_env(t_data *data, const char *var, const char *new_val)
{
	t_env	*elem;
	char	*new_token;
	char	*tmp;

	elem = data->env;
	if (!ft_strcmp(var, "PWD"))
		data->pwd = ft_strdup(new_val);
	if (new_val)
	{
		tmp = ft_strjoin(var, "=");
		if (!tmp)
			return (1);
		new_token = ft_strjoin(tmp, new_val);
		free(tmp);
	}
	else
		new_token = ft_strdup(var);
	if (!new_token)
		return (1);
	while (elem)
	{
		if (ft_strcmp(elem->var, var) == '=' || ft_strcmp(elem->var, var) == -'=')
		{
			free(elem->var);
			elem->var = new_token;
			return (0);
		}
		elem = elem->next;
	}
	elem = get_last(data->env);
	ft_envadd_back(&elem, ft_envnew(new_token));
	return (0);
}

/*
** Returns the value of an environment variable.
** @param env the environment variables list
** @param var the variable name
** @return the value of the environment variable, or NULL if it is not found
*/
char	*get_env(t_env *env, const char *var)
{
	t_env	*elem;
	char	*value;

	elem = env;
	while (elem)
	{
		if (ft_strcmp(elem->var, var) == '=')
		{
			value = ft_strchr(elem->var, '=');
			if (value)
				return (ft_strdup(++value));
			else
				return (NULL);
		}
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
int	del_env(t_env *env, const char *var)
{
	t_env	*elem;

	elem = env;
	while (elem)
	{
		if (ft_strcmp(elem->var, var) == '=')
		{
			elem = find_env_node(env, var);
			if (del_elem(get_previous(env, elem), elem))
				return (1);
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}

/*
** Prints the environment variables.
** @param env the environment variables list
** @return 0 if successful, -1 otherwise
*/
int	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strchr(tmp->var, '='))
			printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	return (0);
}
