/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:59:24 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/26 12:00:16 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	error_export_var(char *arg)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	export_var(t_data *data, char *arg)
{
	int		result;
	char	*value;

	result = 0;
	value = arg;
	if (!(*arg == '_') && !ft_isalpha(*arg))
		return (error_export_var(arg));
	while (*value && *value != '=')
	{
		if (!(*value == '_') && !ft_isalnum(*value))
			return (error_export_var(arg));
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
int	export(t_data *data, char **args)
{
	int	i;
	int	result;

	i = -1;
	if (!args[0])
		return (export_print(data->env));
	while (args[++i])
	{
		result = export_var(data, args[i]);
		if (result)
			return (result);
	}
	return (0);
}
