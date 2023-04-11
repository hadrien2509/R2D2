/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:08:12 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/11 13:09:51 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_tab(char **command)
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

static int	check_n(const char *str)
{
	char	*tmp;

	tmp = (char *)str;
	while (*tmp)
	{
		if (*tmp++ != 'n' && *(tmp))
			return (-1);
	}
	return (1);
}

int	echo(char **command)
{
	int	i;
	int	there_is_command;

	i = 1;
	there_is_command = 0;
	while (command[i] && there_is_command != -1 && command[i][0] == '-')
	{
		there_is_command = check_n(&command[i][1]);
		if (there_is_command == 1)
			i++;
	}
	if (command[i])
		print_tab(&command[i]);
	if (there_is_command != 1)
		printf("\n");
	return (0);
}
