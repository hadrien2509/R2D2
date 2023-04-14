/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/04/14 14:06:53 by sde-smed         ###   ########.fr       */
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
	int		result;
	int		nb_elem;

	result = 0;
	if (!arg)
		return (export_print(data->env));
	if (arg[0] >= '0' && arg[0] <= '9')
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	args = ft_split(arg, '=');
	nb_elem = ft_nb_split(args);
	if (nb_elem == 0 || nb_elem > 2)
		return (1);
	if (nb_elem == 1)
		result = set_env(data, arg, NULL);
	else
		result = set_env(data, args[0], args[1]);
	ft_free_split(args);
	return (result);
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

/*
** Changes the current working directory.
** @param env the shell's environment variables
** @param pwd the current path
** @param str the path to change to
** @return 0 if successful, 1 otherwise
*/
int	builtin_cd(t_data *data, char *str)
{
	char	*path;

	if (!str)
		return (0);
	path = get_absolute_path(data->env, data->pwd, str);
	if (!path || access(path, F_OK) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		if (str[0] == '-')
		{
			str[2] = 0;
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]\n", 2);
			return (1);
		}
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (chdir(path))
		return (1);
	set_env(data, "OLDPWD", data->pwd);
	set_env(data, "PWD", path);
	return (0);
}
