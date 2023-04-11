/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:52:28 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/11 15:00:08 by sde-smed         ###   ########.fr       */
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

	elem = env;
	while (elem)
	{
		if (ft_strcmp(var, elem->var) == -61)
		{
			free(elem->var);
			elem->var = ft_strjoin(var, "=");
			elem->var = ft_strjoin(elem->var, new_val);
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}

char	*get_env(t_env *env, char *var)
{
	t_env	*elem;
	char	*value;

	elem = env;
	while (elem)
	{
		if (ft_strcmp(var, elem->var) == -61)
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

int	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	return (1);
}
