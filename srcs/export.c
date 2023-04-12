/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/04/12 20:06:25 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

		//free split
int	export(t_env *env, char *arg)
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
	if (!args[1])
	{
		ft_free_split(args);
		return (1);
	}
	if (set_env(env, args[0], args[1]))
	{
		ft_free_split(args);
		return (1);
	}
	return (0);
}

int	unset(t_env *env, char *arg)
{
	if (del_env(env, arg))
		return (1);
	return (0);
}
