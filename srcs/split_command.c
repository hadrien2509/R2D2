/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:41:13 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/06 14:15:28 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_string_concatenation(t_handle *handle, char *ptr, char *tmp)
{
	int	size;

	size = 0;
	if (tmp != ptr)
	{
		handle->command = ft_strjoin(handle->command, ptr);
		if (!handle->command)
			return (-1);
	}
	tmp++;
	size = ft_strlen(handle->command);
	handle->command = ft_strjoin(handle->command, tmp);
	if (!handle->command)
		return (-1);
	return (size);
}

static char	*handle_quotes(t_data *data, char *ptr, t_handle *handle)
{
	char	quote;
	char	*tmp;
	int		size;

	size = 0;
	quote = *ptr;
	*ptr = '\0';
	tmp = ++ptr;
	while (*tmp && *tmp != quote)
		tmp++;
	if (*tmp == quote)
	{
		*tmp = '\0';
		if (quote != '\'' && !ft_isempty(ptr))
			ptr = replace_env_variables(data, ptr);
		size = handle_string_concatenation(handle, ptr, tmp);
		if (size == -1)
			return (NULL);
	}
	tmp = handle->command + size;
	return (add_empty(handle, tmp));
}

static char	*handle_dollar_env(t_data *data, char *ptr, char c)
{
	char	*new_ptr;
	char	*tmp;

	tmp = ptr;
	while ((tmp + 1) && *(tmp + 1))
		tmp++;
	if (*tmp == '$' && (c == '"' || c == '\''))
	{
		*tmp = '\0';
		new_ptr = ft_strdup(ptr);
	}
	else
		new_ptr = replace_env_variables(data, ptr);
	return (new_ptr);
}

static char	*handle_dollar_sign(t_data *data, char *ptr, t_handle *handle)
{
	char	*new_ptr;
	int		size;
	char	c;
	char	*tmp;

	tmp = ptr;
	tmp++;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_' || *tmp == '?'))
		tmp++;
	c = *tmp;
	*tmp = '\0';
	new_ptr = handle_dollar_env(data, handle->command, c);
	if (!new_ptr)
		return (NULL);
	*ptr = '\0';
	*tmp = c;
	ptr = ft_strdup(tmp);
	if (!ptr)
		return (NULL);
	free(handle->command);
	handle->command = new_ptr;
	size = ft_strlen(new_ptr);
	if (!ft_join_and_assign(&(handle->command), ptr))
		return (NULL);
	return ((handle->command + size));
}

t_split_elem	*split_command(t_data *data, char *cmd)
{
	t_split_elem	*first;
	char			*ptr;
	t_handle		handle;

	first = NULL;
	init_handle(&handle, data, &first, cmd);
	ptr = handle.command;
	while (ptr && *ptr)
	{
		if (*ptr == '>' || *ptr == '<' || *ptr == '|')
			ptr = handle_special_chars(ptr, &handle);
		else if (ft_is_space(*ptr))
			ptr = handle_spaces(ptr, &handle);
		else if (ft_is_quote(*ptr))
			ptr = handle_quotes(data, ptr, &handle);
		else if (*ptr == '$')
			ptr = handle_dollar_sign(data, ptr, &handle);
		else
			ptr++;
	}
	if (!ft_isempty(handle.command))
		add_command(&handle, handle.command, 0);
	free(handle.command);
	return (first);
}
