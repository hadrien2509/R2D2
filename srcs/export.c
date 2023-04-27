/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:59:24 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/27 14:03:26 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_var(t_data *data, char *arg)
{
	int		result;
	char	*value;

	result = 0;
	value = arg;
	if (!(*arg == '_') && !ft_isalpha(*arg))
		return (print_error("export", "not a valid identifier", arg, 1));
	while (*value && *value != '=')
	{
		if (!(*value == '_') && !ft_isalnum(*value))
			return (print_error("export", "not a valid identifier", arg, 1));
		value++;
	}
	value = ft_strchr(arg, '=');
	if (value && ++value)
	{
		*(value - 1) = 0;
		result = set_env(data, arg, value);
	}
	else
		result = set_env(data, arg, NULL);
	return (result);
}

/*
** Adds or updates an environment variable.
** @param env the environment variables list
** @param var the variable name and value separated by "="
** @return 0 if successful, 1 otherwise
*/
int	export(int fd, t_data *data, char **args)
{
	int	i;
	int	result;

	i = -1;
	if (!args[0])
		return (export_print(fd, data->env));
	while (args[++i])
	{
		result = export_var(data, args[i]);
		if (result)
			return (result);
	}
	return (0);
}
