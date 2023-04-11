/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:34:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/11 15:03:20 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*idk(char *path, char *name)
{
	char	*binary_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	binary_path = ft_strjoin(temp, name);
	free(temp);
	if (access(binary_path, F_OK) == 0)
		return (binary_path);
	free(binary_path);
	return (NULL);
}

static char	*get_binary_path(char *name)
{
	char	**path_list;
	char	*binary_path;
	char	*path_env;
	int		i;

	if (name[0] == '/')
		return (ft_strdup(name));
	i = -1;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_list = ft_split(path_env, ':');
	if (!path_list)
		return (NULL);
	while (path_list[++i])
	{
		binary_path = idk(path_list[i], name);
		if (binary_path)
		{
			free_tab(path_list);
			return (binary_path);
		}
	}
	free_tab(path_list);
	return (NULL);
}

int	exec(char **args, t_data *data)
{
	char	*binary_path;
	int		pid;
	int		result;

	binary_path = get_binary_path(args[0]);
	if (!binary_path)
	{
		printf("%s %s: command not found\n", PROMPT, args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(binary_path, args, env_list_to_tab(data->env_size, data->env));
		free(binary_path);
		perror("execve");
		exit(1);
	}
	free(binary_path);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	waitpid(pid, &result, 0);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(ERROR);
	return (result);
}

int	check_command(char **command, t_data *data)
{
	int	i;

	i = -1;
	if (!command[0])
		return (42);
	else if (!ft_strcmp(command[0], "pwd"))
		return (printf("%s\n", get_env(data->env, "PWD")));
	else if (!ft_strcmp(command[0], "cd"))
		return (cd(data->env, command[1]));
	else if (!ft_strcmp(command[0], "echo"))
		return (echo(command));
	else if (!ft_strcmp(command[0], "exit"))
	{
		printf("exit\n");
		exit(0);
	}
	else if (!ft_strcmp(command[0], "env"))
		return (print_env(data->env));
	else
		return (exec(command, data));
}
