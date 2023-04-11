/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:00:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/11 13:59:46 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*dirname(char *path)
{
	char	*last_slash;

	last_slash = ft_strrchr(path, '/');
	if (!last_slash)
		return (".");
	if (last_slash == path)
	{
		if (*(last_slash + 1) == '\0')
			return ("/");
		else
		{
			*(last_slash + 1) = '\0';
			return (path);
		}
	}
	*(last_slash) = '\0';
	while (last_slash > path && *(last_slash - 1) == '/')
		*(--last_slash) = '\0';
	if (last_slash == path)
		return ("/");
	return (path);
}

static char	*get_absolute_path(char *current_path, char *relative_path)
{
	char	**parts;
	char	*tmp;
	int		i;

	i = -1;
	if (relative_path[0] == '/')
		return (ft_strdup(relative_path));
	parts = ft_split(relative_path, '/');
	while (parts[++i])
	{
		if (!ft_strcmp(parts[i], ".."))
			current_path = dirname(current_path);
		else if (ft_strcmp(parts[i], "."))
		{
			tmp = current_path;
			current_path = ft_strjoin(current_path, "/");
			current_path = ft_strjoin(current_path, parts[i]);
			free(tmp);
		}
	}
	return (current_path);
}

int	cd(t_env *env, char *str)
{
	char	*path;

	path = get_absolute_path(get_env(env, "PWD"), str);
	if (access(path, F_OK) != 0)
	{
		printf("cd: %s: No such file or directory\n", str);
		return (1);
	}
	chdir(path);
	set_env(env, "OLDPWD", get_env(env, "PWD"));
	set_env(env, "PWD", path);
	return (0);
}
