/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:22:45 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/08 13:41:50 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_cmd(t_parse *parse, t_data *data)
{
	int		child;
	int		result;
	char	*cmd;

	cmd = parse->cmd[0];
	result = 0;
	if (is_directory(cmd))
		return (print_error("minishell", "is a directory", cmd, 126));
	if (!can_execute(cmd))
		return (print_error("minishell", "Permission denied", cmd, 126));
	child = fork();
	result = execute(parse, data, child);
	if (parse->pipe_out)
		close(parse->pipe_out);
	return (result);
}

int	builtins(t_data *data, t_parse *parse, int fd)
{
	char	*cmd;
	char	**args;

	cmd = parse->cmd[0];
	args = &parse->cmd[1];
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

static int	exec_builtins(t_parse *parse, t_data *data, int fd)
{
	int	pid;

	if (!parse->pipe_in && !parse->pipe_out)
		return (builtins(data, parse, fd));
	pid = 1;
	pid = fork();
	if (pid == 0)
	{
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			quit(data, ERROR);
		exit (builtins(data, parse, fd));
	}
	exec_exit_handler(pid, data);
	return (0);
}

static void	wait_process(t_data *data)
{
	int	result;

	if (data->family)
	{
		while (data->family)
		{
			if (waitpid(*((int *)data->family->content), &result, 0) == -1)
				exit(1);
			data->family = data->family->next;
		}
		if (signal(SIGINT, signal_handler) == SIG_ERR)
			exit(ERROR);
		if (result == SIGINT)
			data->exit_status = 130;
		else if (result == SIGQUIT)
			data->exit_status = 131;
		else
			data->exit_status = result / 256;
	}
}

static void	check_command_parse(t_parse	*parse, t_data *data)
{
	char	*val;
	int		res;

	val = 0;
	res = 0;
	if (parse->cmd && parse->cmd[0])
	{
		val = parse->cmd[0];
		parse->cmd[0] = get_cmd_path(parse->cmd[0], data);
	}
	if (parse->cmd && !parse->cmd[0] && val)
	{
		if (ft_strchr(val, '/') != NULL)
			res = print_error(val, "No such file or directory", NULL, 127);
		else if (ft_strcmp(".", val) == 0)
		{
			res = print_error(val, "filename argument required", NULL, 2);
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		}
		else
			res = print_error(val, "command not found", NULL, 127);
	}
	if (val)
		free(val);
	data->exit_status = res;
}

void	exec_line(t_parse *parse, t_data *data)
{
	while (parse)
	{
		check_command_parse(parse, data);
		if (parse->cmd && parse->cmd[0])
		{
			parse->in = ft_lstlastinout(parse->in);
			parse->out = ft_lstlastinout(parse->out);
			if (check_builtins(parse->cmd[0]))
			{
				if (parse->out)
					data->exit_status = exec_builtins(parse, data,
							parse->out->fd);
				else if (parse->pipe_out)
					data->exit_status = exec_builtins(parse, data,
							parse->pipe_out);
				else
					data->exit_status = exec_builtins(parse, data, 1);
			}
			else
				data->exit_status = exec_cmd(parse, data);
		}
		close_fd(parse);
		parse = parse->next;
	}
	wait_process(data);
}
