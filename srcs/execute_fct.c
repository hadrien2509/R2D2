/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:57:49 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/02 12:50:20 by sde-smed         ###   ########.fr       */
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

void	exec_exit_handler(int pid, t_data *data)
{
	t_list	*node;
	int		*new_pid;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	new_pid = malloc(sizeof(int));
	if (!new_pid)
		exit (42);
	*new_pid = pid;
	node = ft_lstnew(new_pid);
	if (!node)
		exit (42);
	ft_lstadd_back(&data->family, node);
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
	exec_exit_handler(pid, data);
	return (0);
}
