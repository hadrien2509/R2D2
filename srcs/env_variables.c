/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:25 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/29 16:36:08 by samy             ###   ########.fr       */
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
		if (!ft_join_and_assign(&result, *tmp))
			return (NULL);
	}
	else if (ft_isalpha(*ptr) || *ptr == '_' || *ptr == '-')
	{
		*tmp = find_env_variable(&ptr);
		env = get_env(data->env, *tmp);
		if (env && !ft_join_and_assign(&result, env))
			return (NULL);
	}
	else if (!ft_join_and_assign(&result, "$"))
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
		if (!ft_join_and_assign(&result, command))
			return (NULL);
		command = ptr;
		result = extract_env_name(data, result, ptr, &tmp);
		if (!result)
			return (NULL);
		if (tmp)
			command += ft_strlen(tmp);
		ptr = ft_strchr(command, '$');
		if (!ptr)
			if (!ft_join_and_assign(&result, command))
				return (NULL);
	}
	return (result);
}

char	*replace_env_variables(t_data *data, char *command)
{
	char	*result;
	char	*ptr;

	ptr = ft_strchr(command, '$');
	if (!ptr || !*(ptr))
		return (ft_strdup(command));
	if (ptr != command && *(ptr - 1) && *(ptr - 1) == '\\')
		if (ptr != command || !*(ptr - 2) || *(ptr - 2) != '\\')
			return (ft_strdup(++command));
	if (!*(ptr + 1))
		return (ft_strdup("$"));
	if (*(ptr + 1) == '"' || *(ptr + 1) == '\'')
		return (strdup(++command));
	result = set_env_variable(data, command, ptr);
	return (result);
}
