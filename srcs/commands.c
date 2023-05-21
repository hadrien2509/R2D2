/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:34:52 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/21 14:57:58 by samy             ###   ########.fr       */
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
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	binary_path = ft_strjoin(tmp, name);
	free(tmp);
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
