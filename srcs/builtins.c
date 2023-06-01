/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/06/01 13:12:09 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_env *env, char **names)
{
	int		i;
	char	*arg;

	i = -1;
	if (names[0] && *(names[0]) == '-')
		return (print_error("export", "invalid option", names[0], 2));
	while (names[++i])
	{
		arg = names[i];
		if (ft_isempty(arg))
			return (1);
		if (!(*arg == '_') && !ft_isalpha(*arg))
			return (print_error("export", "not a valid identifier", arg, 1));
		while (*arg)
		{
			if (!ft_isalnum(*arg) && *arg != '_')
				return (print_error("export", "not a valid identifier", arg,
						1));
			arg++;
		}
		del_env(env, names[i]);
	}
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

int	ft_exit_builtin(t_data *data, char **args)
{
	long long	result;
	long long	*value;
	int			elem;

	elem = ft_nb_split(args);
	if (elem == 0)
	{
		ft_putstr_fd("exit\n", 2);
		quit(data, data->exit_status);
	}
	else if (elem != 1)
		quit(data, print_error("exit", "too many arguments", NULL, 1));
	value = ft_atoll(args[0], &result);
	if (!ft_str_is_numeric(args[0]) || !value)
	{
		if (ft_strcmp(args[0], "-9223372036854775808") == 0)
			quit(data, 0);
		quit(data, print_error("exit", "numeric argument required", args[0], -1));
	}
	quit(data, (unsigned char)result);
	return (0);
}
