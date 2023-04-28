/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:25:54 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/28 11:28:15 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Clears the linked list containing environment variables.
** @param lst the address of a pointer to the first node of the list
*/
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

/*
** Allocates and initializes a new environment variable node
** with a copy of a given string.
** @param var the string to copy
** @return a pointer to the new node, or NULL if the allocation fails
*/
t_env	*ft_envnew(const char *name, const char *value)
{
	t_env	*new;

	if (!name)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else
		value = NULL;
	new->next = NULL;
	return (new);
}

/*
** Adds a new environment variable node at the end of a linked list.
** @param alst the address of a pointer to the first node of the list,
	or NULL if the list is empty
** @param new a pointer to the new node to add
*/
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

/*
** Initializes the data struct with a newly created linked list of environment
** variables from a null-terminated string array.
** @param data a pointer to the data struct to initialize
** @param env the null-terminated string array to copy from
** @return 0 if successful, -1 if the allocation fails
*/
int	init_data(t_data *data, char **env)
{
	int		shell_lvl;
	char	*shlvl;

	shell_lvl = 0;
	data->exit_status = 0;
	data->env = ft_strarr_to_env(data, env);
	if (!data->env)
		return (1);
	set_env(data, "OLDPWD", NULL);
	shlvl = get_env(data->env, "SHLVL");
	if (shlvl)
		shell_lvl = ft_atoi(shlvl);
	if (shell_lvl < 0)
		set_env(data, "SHLVL", "0");
	else
		set_env(data, "SHLVL", ft_itoa(++shell_lvl));
	data->pwd = get_env(data->env, "PWD");
	if (!data->pwd)
		return (1);
	return (0);
}

/*
** Deletes the given node in a linked list and frees its memory.
** @param prev the previous node of the node to be deleted,
	NULL if the node to be deleted is the head
** @param to_del the node to be deleted
** @return 0 if successful, 1 if the node to be deleted is NULL
*/
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
