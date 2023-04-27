/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:00:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/27 10:22:49 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Returns the parent directory name of a path.
** @param path the path to extract the parent directory name from
** @return the parent directory name of the path
*/
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

/*
** Joins two paths together by adding a '/' between them.
** @param current_path the path to add the part to
** @param part the part to add to the path
** @return the joined path or NULL if an error occurred
*/
static char	*join_paths(char *current_path, char *part)
{
	char	*tmp;
	char	*new_path;

	tmp = current_path;
	current_path = ft_strjoin(current_path, "/");
	free(tmp);
	if (!current_path)
		return (NULL);
	tmp = ft_strjoin(current_path, part);
	free(current_path);
	if (!tmp)
		return (NULL);
	new_path = tmp;
	return (new_path);
}

/*
** Builds an absolute path from a current path and an array of parts.
** @param current_path the current path to start building the absolute path from
** @param parts the array of parts to add to the current path
** @return the absolute path or NULL if an error occurred
*/
static char	*build_absolute_path(char *current_path, char **parts)
{
	char	*path;
	int		i;

	i = -1;
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
	if (path)
	{
		new_path = ft_strjoin(home, &path[1]);
		free(path);
	}
	else
		new_path = ft_strdup(home);
	return (new_path);
}

/*
** Gets the absolute path of a relative / absolute path by joining it to
**	the current path.
** @param current_path the current path to use as a base for the relative path
** @param relative_path the relative path to get the absolute path for
** @return the absolute path or NULL if an error occurred
*/
char	*get_absolute_path(t_env *env, char *pwd, char *relative_path)
{
	char	**parts;
	char	*path;
	char	*curr_path;

	curr_path = ft_strdup(pwd);
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
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (path);
	}
	parts = ft_split(relative_path, '/');
	path = build_absolute_path(curr_path, parts);
	ft_free_split(parts);
	return (path);
}
