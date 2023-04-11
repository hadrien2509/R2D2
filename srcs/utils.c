/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:25:54 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/11 15:05:09 by sde-smed         ###   ########.fr       */
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
