/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:18:10 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/30 00:52:52 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_strarr_to_env(t_data *data, char **strarr)
{
	t_env	*head;
	t_env	*node;
	char	*value;

	data->env_size = -1;
	head = NULL;
	while (strarr[++data->env_size])
	{
		value = ft_strchr(strarr[data->env_size], '=');
		if (value && ++value)
		{
			*(value - 1) = 0;
			node = ft_envnew(strarr[data->env_size], value);
		}
		else
			node = ft_envnew(strarr[data->env_size], "");
		if (!node)
		{
			ft_envclear(&head);
			return (NULL);
		}
		ft_envadd_back(&head, node);
	}
	return (head);
}

static char	**add_to_tab(t_env *node, char **env, int i)
{
	char	*tmp;

	tmp = ft_strjoin(node->name, "=");
	if (!tmp)
	{
		while (i--)
			free(env[i]);
		free(env);
		return (NULL);
	}
	env[i] = ft_strjoin(tmp, node->value);
	free(tmp);
	if (!env[i])
	{
		while (i--)
			free(env[i]);
		free(env);
		return (NULL);
	}
	return (env);
}

char	**env_list_to_tab(size_t env_size, t_env *first)
{
	char	**env;
	char	**tmp;
	size_t	i;
	t_env	*node;

	node = first;
	env = (char **)malloc((env_size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->value)
		{
			tmp = add_to_tab(node, env, i++);
			if (!tmp)
				return (NULL);
			env = tmp;
		}
		node = node->next;
	}
	env[i - 1] = NULL;
	return (env);
}
