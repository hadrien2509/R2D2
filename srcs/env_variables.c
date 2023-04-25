/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:25 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/25 12:58:30 by hgeissle         ###   ########.fr       */
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
		{
			result = ft_strjoin(result, "$");
			return (result);
		}
		*ptr = 0;
		ptr++;
		result = ft_strjoin(result, command);
		command = ptr;
		if (ft_is_space(*ptr))
			result = ft_strjoin(result, "$");
		if (*ptr == '?')
		{
			tmp = ft_itoa(data->exit_status);
			result = ft_strjoin(result, tmp);
			command += ft_strlen(tmp);
		}
		else
		{
			tmp = find_env_variable(&ptr);
			command += ft_strlen(tmp);
			tmp = get_env(data->env, tmp);
			if (tmp)
				result = ft_strjoin(result, tmp);
		}
		ptr = ft_strchr(command, '$');
		if (!ptr)
			result = ft_strjoin(result, command);
	}
	return (result);
}
