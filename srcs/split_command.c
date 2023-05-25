/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:41:13 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/25 14:00:13 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_string_concatenation(char **cmd, char *ptr, char *tmp)
{
	int	size;

	size = 0;
	if (tmp != ptr)
	{
		*cmd = ft_strjoin(*cmd, ptr);
		if (!*cmd)
			return (-1);
	}
	tmp++;
	size = ft_strlen(*cmd);
	*cmd = ft_strjoin(*cmd, tmp);
	if (!*cmd)
		return (-1);
	return (size);
}

static char	*get_next_quote(t_data *data, char *ptr, char **cmd)
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
		if (!ft_isempty(*cmd))
			*cmd = replace_env_variables(data, *cmd);
		size = handle_string_concatenation(cmd, ptr, tmp);
		if (size == -1)
			return (NULL);
	}
	tmp = *cmd + size;
	return (tmp);
}

static char	*handle_quotes(t_data *data, char *ptr,t_handle *handle)
{
	char c;
	char *after;
	char *tmp;

	ptr = get_next_quote(data, ptr, handle->command);
	after = ptr;
	while(*ptr && *ptr != ' ')
		ptr++;
	c = *ptr;
	*(ptr) = '\0';
	tmp = ft_strdup(replace_env_variables(data, after));
	*after = 0;
	ft_join_and_asign(handle->command, tmp);
	add_command_to_list(handle, *(handle->command), 0);
	*(ptr) = c;
	*(handle->command) = ptr;
	return (ptr);
}

void	init_handle(t_handle *handle, t_data *data, t_list **first,
		char **command)
{
	handle->data = data;
	handle->first = first;
	handle->command = command;
}

t_list	*split_command(t_data *data, char *command)
{
	t_list		*first;
	char		*ptr;
	t_handle	handle;

	first = NULL;
	ptr = command;
	init_handle(&handle, data, &first, &command);
	while (ptr && *ptr && *ptr != '#')
	{
		if (*ptr == '>' || *ptr == '<' || *ptr == '|')
			ptr = handle_special_chars(ptr, &handle);
		else if (ft_is_space(*ptr))
			ptr = handle_spaces(ptr, &handle);
		else if (ft_is_quote(*ptr))
			ptr = handle_quotes(data, ptr, &handle);
		else
			ptr++;
	}
	if (*ptr && *ptr == '#')
		*ptr = '\0';
	add_command_to_list(&handle, command, 1);
	return (first);
}
