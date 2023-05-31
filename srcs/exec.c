/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:22:45 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/31 14:00:59 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_io(t_parse *parse)
{
	if (parse->in)
		dup2(parse->in->fd, 0);
	else if (parse->pipe_in)
		dup2(parse->pipe_in, 0);
	if (parse->out)
		dup2(parse->out->fd, 1);
	else if (parse->pipe_out)
		dup2(parse->pipe_out, 1);
}

int	execute(t_parse *parse, t_data *data, int pid)
{
	int		result;
	char	**env_list;

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			exit(ERROR);
		handle_io(parse);
		env_list = env_list_to_tab(data->env_size, data->env);
		if (!env_list)
			exit(42);
		if (execve(parse->cmd[0], parse->cmd, env_list) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	if (waitpid(pid, &result, 0) == -1)
		return (1);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(ERROR);
	if (result == SIGINT)
		result = 130 * 256;
	else if (result == SIGQUIT)
		result = 131 * 256;
	return (result / 256);
}

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

static int	exec_builtins(t_parse *parse, t_data *data, int fd)
{
	if (!ft_strcmp(parse->cmd[0], "pwd"))
	{
		ft_putstr_fd(data->pwd, fd);
		write(fd, "\n", 1);
		return (0);
	}
	else if (!ft_strcmp(parse->cmd[0], "cd"))
		return (builtin_cd(data, parse->cmd[1]));
	else if (!ft_strcmp(parse->cmd[0], "echo"))
		return (builtin_echo(fd, parse->cmd));
	else if (!ft_strcmp(parse->cmd[0], "export"))
		return (export(fd, data, &parse->cmd[1]));
	else if (!ft_strcmp(parse->cmd[0], "unset"))
		return (unset(data->env, &parse->cmd[1]));
	else if (!ft_strcmp(parse->cmd[0], "env"))
		return (print_env(fd, data->env));
	else if (!ft_strcmp(parse->cmd[0], "exit"))
		return (ft_exit(data, &parse->cmd[1]));
	return (0);
}

void	exec_line(t_parse *parse, t_data *data)
{
	while (parse)
	{
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
		if (parse->pipe_out)
			close(parse->pipe_out);
		parse = parse->next;
	}
}
