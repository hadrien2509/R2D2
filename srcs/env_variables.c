/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:25 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/23 15:47:23 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_env_variable(char **str)
{
	char	*result;
	char	*command;
	char	c;

	c = 0;
	command = *str;
	while (*command && (*command == '_' || ft_isalnum(*command)))
		command++;
	if (*command)
	{
		c = *command;
		*command = '\0';
	}
	result = ft_strdup(*str);
	if (c)
		*command = c;
	return (result);
}

static char	*extract_env_name(t_data *data, char *result, char *ptr, char **tmp)
{
	char	*env;

	if (*ptr == '?')
	{
		*tmp = ft_itoa(data->exit_status);
		if (!ft_join_and_asign(&result, *tmp))
			return (NULL);
	}
	else if (ft_isalpha(*ptr) || *ptr == '_' || *ptr == '-')
	{
		*tmp = find_env_variable(&ptr);
		env = get_env(data->env, *tmp);
		if (env && !ft_join_and_asign(&result, env))
			return (NULL);
	}
	else if (!ft_join_and_asign(&result, "$"))
		return (NULL);
	return (result);
}

char	*set_env_variable(t_data *data, char *command, char *ptr)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (ptr && *ptr)
	{
		tmp = NULL;
		*(ptr++) = 0;
		if (!ft_join_and_asign(&result, command))
			return (NULL);
		command = ptr;
		result = extract_env_name(data, result, ptr, &tmp);
		if (!result)
			return (NULL);
		if (tmp)
			command += ft_strlen(tmp);
		ptr = ft_strchr(command, '$');
		if (!ptr)
			if (!ft_join_and_asign(&result, command))
				return (NULL);
	}
	return (result);
}

char	*replace_env_variables(t_data *data, char *command)
{
	char	*result;
	char	*ptr;

	ptr = ft_strchr(command, '$');
	if (!ptr)
		return (command);
	if (!*(ptr + 1))
		return (command);
	result = set_env_variable(data, command, ptr);
	if (result && !ft_strcmp(result, ""))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
