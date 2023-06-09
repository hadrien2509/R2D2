/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:57:49 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/09 13:07:49 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_signal(t_data *data, int result)
{
	if (result == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
		data->exit_status = 130;
	}
	else if (result == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 2);
		data->exit_status = 131;
	}
	else
		data->exit_status = result / 256;
}

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

int	exec_exit_handler(int pid, t_parse *parse)
{
	pid_t	*new_pid;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	new_pid = malloc(sizeof(pid_t));
	if (!new_pid)
		return (42);
	*new_pid = pid;
	free(parse->pid);
	parse->pid = new_pid;
	return (0);
}

int	execute(t_parse *parse, t_data *data, int pid)
{
	char	**env_list;

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			quit(data, ERROR);
		handle_io(parse);
		env_list = env_list_to_tab(data->env_size, data->env);
		if (!env_list)
			quit(data, 42);
		if (execve(parse->cmd[0], parse->cmd, env_list) == -1)
		{
			perror("execve");
			quit(data, 1);
		}
	}
	return (exec_exit_handler(pid, parse));
}
