/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/04 15:58:29 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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

char	*get_binary_path(char *name)
{
	char	**path_list;
	char	*binary_path;
	char	*temp;
	char	*path_env;
	int		i;

	i = 0;
	path_env = getenv("PATH");
	path_list = ft_split(path_env, ':');
	while (path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		binary_path = ft_strjoin(temp, name);
		free(temp);
		if (access(binary_path, F_OK) == 0)
		{
			free_tab(path_list);
			return (binary_path);
		}
		free(binary_path);
		i++;
	}
	free_tab(path_list);
	return (NULL);
}

void	exec(char **args)
{
	char	*binary_path;

	if (ft_strchr(args[0], '/') != NULL)
		binary_path = ft_strdup(args[0]);
	else
		binary_path = get_binary_path(args[0]);
	if (!binary_path)
	{
		printf("%s: command not found\n", args[0]);
		return ;
	}
	if (fork() == 0)
	{
		execve(binary_path, args, NULL);
		perror("execve");
		exit(1);
	}
	wait(NULL);
	free(binary_path);
}

void	check_command(char **command, char *envp[])
{
	int	i;

	i = 0;
	if (!ft_strcmp(command[0], "exit"))
		exit(0);
	if (!ft_strcmp(command[0], "env"))
		while (envp[i++])
			printf("%s\n", envp[i - 1]);
	else
	{
		exec(command);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	char			**command;
	struct termios	curr;
	struct termios	save;

	tcgetattr(STDIN_FILENO, &curr);
	tcgetattr(STDIN_FILENO, &save);
	curr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &curr);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (ERROR);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (ERROR);
	while (1)
	{
		line = readline("minishell-1.0$ ");
		if (!line)
			return (0);
		add_history(line);
		command = ft_split(line, ' ');
		check_command(command, envp);
		free(line);
	}
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}
