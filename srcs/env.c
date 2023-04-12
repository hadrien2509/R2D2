/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:52:28 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/12 13:10:24 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_list_to_tab(unsigned env_size, t_env *first)
{
	char	**env;
	size_t	i;
	t_env	*node;

	node = first;
	env = (char **)malloc((env_size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (node)
	{
		env[i] = ft_strdup(node->var);
		if (!env[i])
		{
			while (i--)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
		node = node->next;
	}
	env[env_size] = NULL;
	return (env);
}

int	set_env(t_env *env, char *var, char *new_val)
{
	t_env	*elem;
	char	*new_token;

	elem = env;
	new_token = ft_strjoin(var, "=");
	new_token = ft_strjoin(new_token, new_val);
	while (elem)
	{
		if (ft_strcmp(var, elem->var) == -61)
		{
			free(elem->var);
			elem->var = new_token;
			return (0);
		}
		elem = elem->next;
	}
	elem = get_last(env);
	ft_envadd_back(&elem, ft_envnew(new_token));
	return (0);
}

char	*get_env(t_env *env, char *var)
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

int	del_env(t_env *env, char *var)
{
	t_env	*elem;

	elem = env;
	while (elem)
	{
		if (ft_strcmp(elem->var, var) == '=')
		{
			elem = get_env_t(env, var);
			if (del_elem(get_previous(env, elem), elem))
				return (1);
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}

int	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	return (0);
}
