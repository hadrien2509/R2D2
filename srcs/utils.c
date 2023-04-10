/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:25:54 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/10 13:58:09 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char    **ft_envlst_to_chararr(t_env *envlst)
{
    char    **env;
    size_t  env_size;
    size_t  i;
    t_env   *node;

    env_size = 0;
    node = envlst;
    while (node)
    {
        env_size++;
        node = node->next;
    }
    env = (char **)malloc((env_size + 1) * sizeof(char *));
    if (!env)
        return (NULL);
    i = 0;
    node = envlst;
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

t_env	*ft_strarr_to_env(char **strarr)
{
	size_t	i;
	t_env	*head;
	t_env	*node;

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
	return (head);
}


int		init_data(t_data *data, char **env)
{
	data->env = ft_strarr_to_env(env);
	if (!data->env)
		return (-1);
	return (0);
}

int	set_env(t_env *env, char *var, char *new_val)
{
	t_env *elem;

	elem = env;
	while (elem)
	{
		if (ft_strcmp(var, elem->var) == -61)
		{
			printf("old : %s\n", elem->var);
			free(elem->var);
			elem->var = ft_strjoin(var, "=");
			elem->var = ft_strjoin(elem->var, new_val);
			printf("new : %s\n", elem->var);
		}
		elem = elem->next;
	}
	return (1);
}
int	get_env(t_env *env, char *var)
{
	t_env *elem;

	elem = env;
	while (elem)
	{
		if (ft_strcmp(var, elem->var) == -61)
		{
			printf("%s\n", elem->var);
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}