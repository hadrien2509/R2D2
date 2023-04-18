/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/04/18 12:12:03 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_var(t_data *data, char *arg)
{
	int		result;
	char	*value;

	result = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	value = ft_strchr(arg, '=');
	if (value && ++value)
	{
		*(value - 1) = 0;
		result = set_env(data, arg, value);
	}
	else
		result = set_env(data, arg, NULL);
	return (result);
}

/*
** Adds or updates an environment variable.
** @param env the environment variables list
** @param var the variable name and value separated by "="
** @return 0 if successful, 1 otherwise
*/
int	export(t_data *data, char **args)
{
	int	i;
	int	result;

	i = -1;
	if (!args[0])
		return (export_print(data->env));
	while (args[++i])
	{
		result = export_var(data, args[i]);
		if (result)
			return (result);
	}
	return (0);
}

/*
** Deletes an environment variable.
** @param env the environment variables list
** @param arg the name of the variable to delete
** @return 0 if successful, 1 otherwise
*/
int	unset(t_env *env, char **names)
{
	int	i;

	i = -1;
	while (names[++i])
		del_env(env, names[i]);
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

int	ft_exit(t_data *data, char **args)
{
	long long	result;
	int			elem;

	elem = ft_nb_split(args);
	if (elem == 0)
		exit(data->exit_status);
	else if (elem != 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (!ft_str_is_numeric(args[0]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	result = ft_atoi_long_long(args[0]);
	result %= 256;
	exit(data->exit_status);
}
