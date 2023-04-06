/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:34:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/07 00:27:10 by samy             ###   ########.fr       */
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

static char	*get_binary_path(char *name)
{
	char	**path_list;
	char	*binary_path;
	char	*temp;
	char	*path_env;
	int		i;

	i = 0;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_list = ft_split(path_env, ':');
	if (!path_list)
		return (NULL);
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

static void	exec(char **args)
{
	char	*binary_path;

	if (ft_strchr(args[0], '/') != NULL)
		binary_path = ft_strdup(args[0]);
	else
		binary_path = get_binary_path(args[0]);
	if (!binary_path)
	{
		printf("minishell_alpha-0.1: %s: No such file or directory\n", args[0]);
		return ;
	}
	if (fork() == 0)
	{
		execve(binary_path, args, NULL);
		perror("execve");
		exit(1);
	}
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	wait(NULL);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(ERROR);
	free(binary_path);
}

void	print_tab(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[++i])
			printf(" ");
	}
}

int	echo_check_para(const char *str)
{
	char	*tmp;

	tmp = (char *)str;
	while (*tmp == 'n')
		if (*(++tmp) && *tmp != 'n')
			return (-1);
	return (1);
}

void	echo(char **command)
{
	int	i;
	int	there_is_command;

	i = 1;
	there_is_command = 0;
	if (command[1])
	{
		while (there_is_command != -1 && command[i][0] == '-')
		{
			there_is_command = echo_check_para(&command[i][1]);
			if (there_is_command)
				i++;
		}
		print_tab(&command[i]);
	}
	if (there_is_command != 1)
		printf("\n");
}

void	check_command(char **command, char *envp[])
{
	int	i;

	i = -1;
	if (!command[0])
		return ;
	else if (!ft_strcmp(command[0], "pwd"))
		printf("%s\n", getenv("PWD"));
	else if (!ft_strcmp(command[0], "cd"))
		chdir(command[1]);
	else if (!ft_strcmp(command[0], "echo"))
		echo(command);
	else if (!ft_strcmp(command[0], "exit"))
		exit(0);
	else if (!ft_strcmp(command[0], "env"))
		while (envp[++i])
			printf("%s\n", envp[i]);
	else
	{
		exec(command);
	}
}
