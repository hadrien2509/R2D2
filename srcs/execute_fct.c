/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:57:49 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/31 17:20:25 by hgeissle         ###   ########.fr       */
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

static int	exec_exit_handler(int pid)
{
	int	result;

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

int	execute(t_parse *parse, t_data *data, int pid)
{
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
	return (exec_exit_handler(pid));
}
