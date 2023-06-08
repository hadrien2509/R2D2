/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:59:24 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/08 11:59:07 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_export_var(t_data *data, char *arg, char *value)
{
	char	*old_value;
	char	*new_value;

	if (*value != '+' || *(value + 1) != '=')
		return (print_error("export", "not a valid identifier", arg, 1));
	*value = 0;
	value += 2;
	old_value = get_env(data->env, arg);
	if (!old_value)
		return (set_env(data, arg, value));
	new_value = ft_strjoin(old_value, value);
	if (!new_value)
		return (42);
	return (set_env(data, arg, new_value));
}

static int	export_var(t_data *data, char *arg)
{
	int		result;
	char	*value;

	result = 0;
	value = arg;
	if (ft_isempty(arg))
		return (print_error("export", "not a valid identifier", "`'", 1));
	if (*arg == '-')
		return (print_error("export", "invalid option", arg, 2));
	if (!(*arg == '_') && !ft_isalpha(*arg))
		return (print_error("export", "not a valid identifier", arg, 1));
	while (*value && *value != '=' && (*value == '_' || ft_isalnum(*value)))
		value++;
	if (value && *value && *value != '=')
		return (add_export_var(data, arg, value));
	if (*value && *++(value))
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
