/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:00:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/14 11:37:41 by sde-smed         ###   ########.fr       */
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

static char	*set_old_pwd(t_env *env, char *relative_path)
{
	char	*path;

	if (!relative_path[1])
	{
		path = get_env(env, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (path);
	}
	return (NULL);
}

static char	*ft_tilde(t_env *env, char *path)
{
	char *home;
	char *new_path;

	home = get_env(env, "HOME");
	new_path = ft_strjoin(home, &path[1]);
	free(path);
	return (new_path);
}

/*
** Gets the absolute path of a relative / absolute path by joining it to
**	the current path.
** @param current_path the current path to use as a base for the relative path
** @param relative_path the relative path to get the absolute path for
** @return the absolute path or NULL if an error occurred
*/
char	*get_absolute_path(t_env *env, char *curr_path, char *relative_path)
{
	char	**parts;
	char	*path;

	if (relative_path[0] == '~')
		relative_path = ft_tilde(env, relative_path);
	if (relative_path[0] == '-')
	{
		if (relative_path[1])
			return (NULL);
		path = set_old_pwd(env, relative_path);
		return (path);
	}
	if (relative_path[0] == '/')
	{
		curr_path = ft_strdup("");
	}
	parts = ft_split(relative_path, '/');
	path = build_absolute_path(curr_path, parts);
	ft_free_split(parts);
	return (path);
}

/*
** Changes the current working directory.
** @param env the shell's environment variables
** @param pwd the current path
** @param str the path to change to
** @return 0 if successful, 1 otherwise
*/
int	builtin_cd(t_data *data, char *str)
{
	char	*path;

	if (!str)
		return (0);
	path = get_absolute_path(data->env, data->pwd, str);
	if (!path || access(path, F_OK) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		if (str[0] == '-')
		{
			str[2] = 0;
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]\n", 2);
			return (1);
		}
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (chdir(path))
		return (1);
	set_env(data, "OLDPWD", data->pwd);
	set_env(data, "PWD", path);
	return (0);
}
