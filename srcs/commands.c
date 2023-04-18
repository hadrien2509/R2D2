/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:34:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/18 12:35:15 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Search for the binary path of the given command name
** in the specified directory.
** @param path the path to the directory to search in
** @param name the name of the command to search for
** @return the binary path if found, NULL otherwise
*/
static char	*check_binary_path(char *path, char *name)
{
	char	*binary_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	binary_path = ft_strjoin(temp, name);
	free(temp);
	if (!binary_path)
		return (NULL);
	if (access(binary_path, F_OK) == 0)
		return (binary_path);
	free(binary_path);
	return (NULL);
}

/*
** Returns the binary path of the given command name.
** @param env a linked list of environment variables
** @param name the name of the command to search for
** @return the binary path if found, NULL otherwise
*/
char	*get_binary_path(t_env *env, char *name)
{
	char	**path_list;
	char	*binary_path;
	char	*path_env;
	int		i;

	binary_path = NULL;
	if (name[0] == '/' || name[0] == '.' || name[0] == '~')
		return (ft_strdup(name));
	i = -1;
	path_env = get_env(env, "PATH");
	if (!path_env)
		return (NULL);
	path_list = ft_split(path_env, ':');
	free(path_env);
	if (!ft_nb_split(path_list))
	{
		ft_free_split(path_list);
		return (NULL);
	}
	while (path_list[++i] && !binary_path)
		binary_path = check_binary_path(path_list[i], name);
	ft_free_split(path_list);
	return (binary_path);
}

/*
** Forks and executes the given command in the child process.
** @param args an array of strings containing the command and its arguments
** @param binary_path the path to the binary for the command
** @param env_list an array of strings containing the environment variables
** @return the exit status of the command
*/
static int	fork_and_execute(char **args, char *binary_path, char **env_list)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (execve(binary_path, args, env_list) == -1)
		{
			free(binary_path);
			free(env_list);
			perror("execve");
			exit(1);
		}
	}
	free(binary_path);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	if (waitpid(pid, &result, 0) == -1)
		return (1);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(ERROR);
	return (result);
}

/*
** Executes the given command.
** @param args an array of strings containing the command and its arguments
** @param data a struct containing the shell's data
** @return the exit status of the command
*/
int	exec(char **args, t_data *data)
{
	char	*binary_path;
	char	**env_list;
	int		result;

	binary_path = get_binary_path(data->env, args[0]);
	if (binary_path)
		binary_path = get_absolute_path(data->env, data->pwd, binary_path);
	if (!binary_path)
	{
		ft_putstr_fd(PROMPT, 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	env_list = env_list_to_tab(data->env_size, data->env);
	result = fork_and_execute(args, binary_path, env_list);
	free(env_list);
	return (result);
}

/*
** Determines the type of the given command and executes it accordingly.
** @param command an array of strings containing the command and its arguments
** @param data a struct containing the shell's data
** @return the exit status of the command
*/
int	check_command(char **command, t_data *data)
{
	if (!command[0])
		return (0);
	else if (!ft_strcmp(command[0], "pwd"))
		return ((printf("%s\n", data->pwd) == 0));
	else if (!ft_strcmp(command[0], "cd"))
		return (builtin_cd(data, command[1]));
	else if (!ft_strcmp(command[0], "echo"))
		return (builtin_echo(command));
	else if (!ft_strcmp(command[0], "export"))
		return (export(data, &command[1]));
	else if (!ft_strcmp(command[0], "unset"))
		return (unset(data->env, &command[1]));
	else if (!ft_strcmp(command[0], "env"))
		return (print_env(data->env));
	else if (!ft_strcmp(command[0], "exit"))
		return (ft_exit(data, &command[1]));
	else
		return (exec(command, data));
}
