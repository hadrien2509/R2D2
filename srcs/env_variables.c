/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:25 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/15 11:37:17 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env_variable(char **str)
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

char	*replace_env_variables(t_data *data, char *command)
{
	char	*tmp;
	char	*result;
	char	*ptr;

	result = ft_strdup("");
	ptr = ft_strchr(command, '$');
	if (!ptr)
		return (command);
	while (ptr && *ptr)
	{
		if (!*(ptr + 1))
			return (ft_strjoin(result, "$"));
		*ptr = 0;
		ptr++;
		result = ft_strjoin(result, command);
		command = ptr;
		if (ft_is_space(*ptr))
		{
			result = ft_strjoin(result, "$");
			if (!result)
				return (NULL);
		}
		if (*ptr == '?')
		{
			tmp = ft_itoa(data->exit_status);
			result = ft_strjoin(result, tmp);
			if (!result)
				return (NULL);
			command += ft_strlen(tmp);
		}
		else
		{
			tmp = find_env_variable(&ptr);
			command += ft_strlen(tmp);
			tmp = get_env(data->env, tmp);
			if (tmp)
			{
				result = ft_strjoin(result, tmp);
				if (!result)
					return (NULL);
			}
		}
		ptr = ft_strchr(command, '$');
		if (!ptr)
			result = ft_strjoin(result, command);
		if (!result)
			return (NULL);
	}
	if (!ft_strcmp(result, ""))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
