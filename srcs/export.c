/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:59:24 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/31 23:03:21 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	export_var(t_data *data, char *arg)
{
	int		result;
	char	*value;

	result = 0;
	value = arg;
	if (*arg == '-')
		return (print_error("export", "invalid option", arg, 2));
	if (!(*arg == '_') && !ft_isalpha(*arg))
		return (print_error("export", "not a valid identifier", arg, 1));
	while (*value && *value != '=' && (*value == '_' || ft_isalnum(*value)))
		value++;
	if (value && *value && *value != '=')
		if (*value != '+' || *(value + 1) != '=')
			return (print_error("export", "not a valid identifier", arg, 1));
	if (value && ++value)
	{
		*(value - 1) = 0;
		result = set_env(data, arg, value);
	}
	else
		result = set_env(data, arg, NULL);
	return (result);
}

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
