/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:00:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/30 01:05:46 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_dirname(char *path)
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

static char	*join_paths(char *current_path, char *part)
{
	char	*tmp;

	tmp = current_path;
	if (ft_strcmp(current_path, "/"))
	{
		tmp = ft_strjoin(current_path, "/");
		free(current_path);
	}
	if (!tmp)
		return (NULL);
	current_path = ft_strjoin(tmp, part);
	free(tmp);
	if (!current_path)
		return (NULL);
	return (current_path);
}

static char	*build_absolute_path(char *current_path, char **parts)
{
	char	*path;
	int		i;

	i = -1;
	if (!parts[0])
		return (ft_strdup("/"));
	while (parts[++i])
	{
		if (!ft_strcmp(parts[i], ".."))
			current_path = ft_dirname(current_path);
		else if (ft_strcmp(parts[i], "."))
		{
			path = join_paths(current_path, parts[i]);
			if (!path)
				return (NULL);
			current_path = path;
		}
	}
	return (current_path);
}

static char	*ft_tilde(t_env *env, char *path)
{
	char	*home;
	char	*new_path;

	home = get_env(env, "HOME");
	if (!ft_isempty(home) && path && path[0] == '~')
	{
		new_path = ft_strjoin(home, &path[1]);
		if (!new_path)
			return (NULL);
		free(path);
	}
	else
		new_path = ft_strdup(home);
	return (new_path);
}

char	*get_absolute_path(t_env *env, char *curr_path, char *relative_path)
{
	char	**parts;
	char	*path;

	if (!relative_path || relative_path[0] == '~')
		relative_path = ft_tilde(env, relative_path);
	if (!relative_path)
		return (NULL);
	if (relative_path[0] == '-')
	{
		if (relative_path[1])
			return (NULL);
		path = get_env(env, "OLDPWD");
		if (!path)
			print_error("cd", "OLDPWD not set", NULL, 0);
		return (path);
	}
	if (relative_path[0] == '/')
		curr_path = ft_strdup("");
	parts = ft_split(relative_path, '/');
	if (!parts)
		return (NULL);
	path = build_absolute_path(curr_path, parts);
	ft_free_split(parts);
	return (path);
}
