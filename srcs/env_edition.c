/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:25:54 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/30 11:26:49 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

static int	allocate_memory(t_env *new, const char *name, const char *value)
{
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (0);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (0);
		}
	}
	else
		new->value = NULL;
	return (1);
}

t_env	*ft_envnew(const char *name, const char *value)
{
	t_env	*new;

	if (!name)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!allocate_memory(new, name, value))
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

int	del_elem(t_env *prev, t_env *to_del)
{
	if (to_del == NULL)
		return (1);
	if (prev == NULL)
	{
		free(to_del->name);
		free(to_del->value);
		free(to_del);
		return (0);
	}
	prev->next = to_del->next;
	free(to_del->name);
	free(to_del->value);
	free(to_del);
	return (0);
}
