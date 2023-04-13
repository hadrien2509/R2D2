/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/04/13 15:45:31 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Adds or updates an environment variable.
** @param env the environment variables list
** @param var the variable name and value separated by "="
** @return 0 if successful, 1 otherwise
*/
int	export(t_data *data, char *arg)
{
	char	**args;

	if (!arg)
		return (1);
	args = ft_split(arg, '=');
	if (ft_nb_split(args) != 2)
	{
		ft_free_split(args);
		return (1);
	}
	if (set_env(data, args[0], args[1]))
	{
		ft_free_split(args);
		return (1);
	}
	ft_free_split(args);
	return (0);
}

/*
** Deletes an environment variable.
** @param env the environment variables list
** @param arg the name of the variable to delete
** @return 0 if successful, 1 otherwise
*/
int	unset(t_env *env, char *arg)
{
	if (del_env(env, arg))
		return (1);
	return (0);
}
