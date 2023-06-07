/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:39:50 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/07 19:05:17 by hgeissle         ###   ########.fr       */
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

	if (ft_isempty(arg))
		return (NULL);
	if (ft_strcmp(arg, ".") == 0)
		return (NULL);
	if (ft_strchr(arg, '/') != NULL)
		path = ft_strdup(arg);
	else if (check_builtins(arg))
		return (ft_strdup(arg));
	else
		path = get_binary_path(data->env, arg);
	if (path)
		path = get_absolute_path(data->env, ft_strdup(data->pwd), path);
	if (!path)
		return (path);
	else if (access(path, F_OK) != 0)
	{
		free(path);
		path = NULL;
	}
	return (path);
}
