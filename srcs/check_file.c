/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:56:18 by samy              #+#    #+#             */
/*   Updated: 2023/05/12 14:57:19 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_directory(char *folder)
{
	struct stat	statbuf;

	if (stat(folder, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	can_execute(char *file)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
		return (0);
	if (file_stat.st_mode & S_IXUSR)
		return (1);
	return (0);
}

int	can_read(char *file)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
		return (0);
	if (file_stat.st_mode & S_IRUSR)
		return (1);
	return (0);
}

int	can_write(char *file)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
		return (0);
	if (file_stat.st_mode & S_IWUSR)
		return (1);
	return (0);
}

int	is_file(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) != 0)
		return (0);
	return (S_ISREG(statbuf.st_mode));
}
