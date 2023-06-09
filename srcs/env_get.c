/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:19:41 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/01 15:34:23 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_env	*get_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

int	init_data(t_data *data, char **env)
{
	int		shell_lvl;
	char	*shlvl;

	shell_lvl = 0;
	data->exit_status = 0;
	data->env = ft_strarr_to_env(data, env);
	set_env(data, "OLDPWD", NULL);
	shlvl = get_env(data->env, "SHLVL");
	if (shlvl)
	{
		shell_lvl = ft_atoi(shlvl);
		free(shlvl);
		shlvl = ft_itoa(++shell_lvl);
		if (shell_lvl > 0)
			set_env(data, "SHLVL", shlvl);
		free(shlvl);
	}
	else if (!shlvl)
		set_env(data, "SHLVL", "1");
	else
		set_env(data, "SHLVL", "0");
	data->pwd = get_env(data->env, "PWD");
	if (!data->pwd)
		return (1);
	return (0);
}
