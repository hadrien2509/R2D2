/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:57:49 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/09 12:15:48 by hgeissle         ###   ########.fr       */
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

// void	sig_pipe_quit(int signal)
// {
// 	dprintf(2, "ok\n");
// 	if (signal == SIGPIPE)
// 		exit (42);
// 	else if (signal == SIGQUIT)
// 	{
// 		ft_putstr_fd("\n^\\Quit: 3\n", 2);
// 		exit (0);
// 	}
// 	else if (signal == SIGINT)
// 	{
// 		ft_putstr_fd("\n^C", 2);
// 		signal_handler(signal);
// 	}
// }

int	execute(t_parse *parse, t_data *data, int pid)
{
	char	**env_list;

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			quit(data, ERROR);
		// if (signal(SIGPIPE, sig_pipe_quit) == SIG_ERR)
		// 	quit(data, ERROR);
		// if (signal(SIGINT, sig_pipe_quit) == SIG_ERR)
		// 	quit(data, ERROR);
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
