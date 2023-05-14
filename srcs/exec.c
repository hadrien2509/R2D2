/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:22:45 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/14 14:34:36 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//check si il faut pas free des trucs quand il y a une error de sig
int	execute(t_Parse *parse, t_data *data, int pid)
{
	int		result;
	char	**env_list;

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (parse->in)
			dup2(parse->in->fd, 0);
		if (parse->out)
			dup2(parse->out->fd, 1);
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
	return (result);
}

int	exec_cmd(t_Parse *parse, t_data *data)
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
	if (parse->out)
		close(parse->out->fd);
	return (result);
}

// 69 -> Ajouter une condition ici
int	exec_builtins(t_Parse *parse, t_data *data, int fd)
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

//110 => printf("exit status = %d\n", data->exit_status);
// if (parse->cmd && parse->out && parse->out->next)
// 	redirec(parse);
void	exec_line(t_Parse *parse, t_data *data)
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
				{
					data->exit_status = exec_builtins(parse, data,
							parse->out->fd);
					close(parse->out->fd);
				}
				else
					data->exit_status = exec_builtins(parse, data, 1);
			}
			else
				data->exit_status = exec_cmd(parse, data);
		}
		parse = parse->next;
	}
}
