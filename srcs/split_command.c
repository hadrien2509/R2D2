/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:41:13 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/30 14:00:50 by sde-smed         ###   ########.fr       */
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
	return (tmp);
}

static char	*handle_dollar_env(t_data *data, char *ptr, char c)
{
	char	*new_ptr;

	if (!ft_strcmp(ptr, "$") && (c == '"' || c == '\''))
		new_ptr = ft_strdup("");
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

t_list	*split_command(t_data *data, char *cmd)
{
	t_list		*first;
	char		*ptr;
	t_handle	handle;

	first = NULL;
	init_handle(&handle, data, &first, cmd);
	ptr = handle.command;
	while (ptr && *ptr && *ptr != '#')
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
	if (ptr && *ptr && *ptr == '#')
		*ptr = '\0';
	add_command_to_list(&handle, handle.command);
	free(handle.command);
	return (first);
}
