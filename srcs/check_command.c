/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:39:50 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/28 12:04:31 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins(char *arg)
{
	if (!ft_strcmp(arg, "pwd"))
		return (1);
	else if (!ft_strcmp(arg, "cd"))
		return (1);
	else if (!ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset"))
		return (1);
	else if (!ft_strcmp(arg, "env"))
		return (1);
	else if (!ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

char	*get_cmd_path(char *arg, t_data *data)
{
	char	*path;

	if (ft_strchr(arg, '/') != NULL)
		path = ft_strdup(arg);
	else if (check_builtins(arg))
	{
		path = ft_strdup(arg);
		return (path);
	}
	else
		path = get_binary_path(data->env, arg);
	if (path)
		path = get_absolute_path(data->env, data->pwd, path);
	if (!path | (access(path, F_OK) != 0))
	{
		free(path);
		print_error(arg, "command not found", NULL, 0);
		data->exit_status = 127;
	}
	return (path);
}
