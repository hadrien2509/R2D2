/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:25:54 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/12 12:54:06 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->var);
		free(*lst);
		*lst = tmp;
	}
}

t_env	*ft_envnew(char *var)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static t_env	*ft_strarr_to_env(t_data *data, char **strarr)
{
	unsigned int	i;
	t_env			*head;
	t_env			*node;

	i = 0;
	head = NULL;
	while (strarr[i])
	{
		node = ft_envnew(strarr[i]);
		if (!node)
		{
			ft_envclear(&head);
			return (NULL);
		}
		ft_envadd_back(&head, node);
		i++;
	}
	data->env_size = ++i;
	return (head);
}

int	init_data(t_data *data, char **env)
{
	data->env = ft_strarr_to_env(data, env);
	if (!data->env)
		return (-1);
	return (0);
}

t_env	*get_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
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

int	del_elem(t_env *prev, t_env *to_del)
{
	if (to_del == NULL)
		return (1);
	if (prev == NULL)
	{
		free(to_del->var);
		free(to_del);
		return (0);
	}
	prev->next = to_del->next;
	free(to_del->var);
	free(to_del);
	return (0);
}

t_env	*get_env_t(t_env *env, char *arg)
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
