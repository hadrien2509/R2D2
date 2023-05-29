/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:08:12 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/29 13:15:47 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_arguments(int fd, char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		ft_putstr_fd(command[i], fd);
		if (command[++i])
			ft_putstr_fd(" ", fd);
	}
}

static int	check_only_n_chars(const char *str)
{
	char	*tmp;

	tmp = (char *)str;
	while (*++tmp)
		if (*tmp != 'n')
			return (-1);
	return (1);
}

int	builtin_echo(int fd, char **command)
{
	int	i;
	int	has_n_option;
	int	tmp;

	i = 1;
	has_n_option = 0;
	tmp = 0;
	if (!command)
		return (1);
	while (command[i] && tmp != -1 && command[i][0] == '-' && command[i][1])
	{
		tmp = check_only_n_chars(&command[i][0]);
		if (tmp == 1)
		{
			has_n_option = 1;
			i++;
		}
	}
	if (command[i])
		print_arguments(fd, &command[i]);
	if (has_n_option != 1)
		ft_putstr_fd("\n", fd);
	return (0);
}
