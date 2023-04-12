/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:08:12 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/12 20:34:28 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Prints the echo.
** @param command the array of strings to print
** @return void
*/
static void	print_arguments(char **command)
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

/*
** Checks if the string is composed only of 'n' characters.
** @param str the string to check
** @return 1 if the string is composed only of 'n' characters, -1 otherwise
*/
static int	check_only_n_chars(const char *str)
{
	char	*tmp;

	tmp = (char *)str;
	while (*tmp)
	{
		if (*tmp++ != 'n' && !*(tmp))
			return (-1);
	}
	return (1);
}

/*
** The built-in echo command prints its arguments separated by a space,
** with a newline character at the end, unless the -n option is specified.
** @param command the array of strings representing the arguments of the command
** @return 0 if successful, -1 otherwise
*/
int	builtin_echo(char **command)
{
	int	i;
	int	has_n_option;
	int	tmp;

	i = 1;
	has_n_option = 0;
	tmp = 0;
	if (!command)
		return (1);
	while (command[i] && tmp != -1 && command[i][0] == '-')
	{
		tmp = check_only_n_chars(&command[i][1]);
		if (tmp == 1)
		{
			has_n_option = 1;
			i++;
		}
	}
	if (command[i])
		print_arguments(&command[i]);
	if (has_n_option != 1)
		printf("\n");
	return (0);
}