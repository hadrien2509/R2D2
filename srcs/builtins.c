/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/05/21 12:17:48 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_env *env, char **names)
{
	int	i;

	i = -1;
	while (names[++i])
		del_env(env, names[i]);
	return (0);
}

int	builtin_cd(t_data *data, char *str)
{
	char	*path;

	path = ft_strdup(data->pwd);
	if (!path)
		return (42);
	path = get_absolute_path(data->env, path, str);
	if (!path || access(path, F_OK) != 0)
	{
		if (str[0] == '-')
		{
			if (str[1] != '\0')
				print_error("cd", "invalid option", str, 1);
			return (1);
		}
		return (print_error("cd", "No such file or directory", str, 1));
	}
	if (!is_directory(path))
		return (print_error("cd", "Not a directory", str, 1));
	if (chdir(path))
		return (1);
	set_env(data, "OLDPWD", data->pwd);
	set_env(data, "PWD", path);
	free(path);
	return (0);
}

int	ft_exit(t_data *data, char **args)
{
	long long	result;
	long long	*value;
	int			elem;

	elem = ft_nb_split(args);
	if (elem == 0)
		exit(data->exit_status);
	else if (elem != 1)
		exit(print_error("exit", "too many arguments", NULL, 1));
	value = ft_atoll(args[0], &result);
	if (!ft_str_is_numeric(args[0]) || !value)
	{
		if (ft_strcmp(args[0], "-9223372036854775808") == 0)
			exit(0);
		exit(print_error("exit", "numeric argument required", args[0], -1));
	}
	exit((unsigned char)result);
}
