/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:25:03 by samy              #+#    #+#             */
/*   Updated: 2023/06/08 20:19:55 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_env *env, char **names)
{
	int		i;
	char	*arg;

	i = -1;
	if (names[0] && ft_isempty(names[0]))
		return (print_error("unset", "not a valid identifier", "`'", 1));
	if (names[0] && *(names[0]) == '-')
		return (print_error("unset", "invalid option", names[0], 2));
	while (names[++i])
	{
		arg = names[i];
		if (ft_isempty(arg))
			return (1);
		if (!(*arg == '_') && !ft_isalpha(*arg))
			return (print_error("unset", "not a valid identifier", arg, 1));
		while (*arg)
		{
			if (!ft_isalnum(*arg) && *arg != '_')
				return (print_error("unset", "not a valid identifier", arg,
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
		quit(data, data->old_exit_status);
	}
	value = ft_atoll(args[0], &result);
	if (ft_isempty(args[0]) || !ft_str_is_numeric(args[0]) || !value)
	{
		if (ft_strcmp(args[0], "-9223372036854775808") == 0)
			quit(data, 0);
		quit(data, print_error("exit", "numeric argument required", args[0],
				-1));
	}
	else if (elem != 1)
		quit(data, print_error("exit", "too many arguments", NULL, 1));
	quit(data, (unsigned char)result);
	return (0);
}

static void	discharge_pipe(t_parse *parse)
{
	int		clear_pipe;
	char	buf[100];

	if (parse->pipe_in)
	{
		clear_pipe = read(parse->pipe_in, buf, 100);
		while (clear_pipe)
			clear_pipe = read(parse->pipe_in, buf, 100);
	}
}

int	builtins(t_data *data, t_parse *parse, int fd)
{
	char	*cmd;
	char	**args;

	cmd = parse->cmd[0];
	args = &parse->cmd[1];
	discharge_pipe(parse);
	if (!ft_strcmp(cmd, "pwd"))
	{
		ft_putstr_fd(data->pwd, fd);
		write(fd, "\n", 1);
		return (0);
	}
	else if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(data, *args));
	else if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(fd, parse->cmd));
	else if (!ft_strcmp(cmd, "export"))
		return (export(fd, data, args));
	else if (!ft_strcmp(cmd, "unset"))
		return (unset(data->env, args));
	else if (!ft_strcmp(cmd, "env"))
		return (print_env(fd, data->env, args));
	else if (!ft_strcmp(cmd, "exit"))
		return (ft_exit_builtin(data, args));
	return (0);
}
