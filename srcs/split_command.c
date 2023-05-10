/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:41:13 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/10 18:50:51 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Add a command to a linked list.
** @param handle a pointer to a t_handle structure containing the necessary data.
** @param str a string containing the command to add.
** @return void.
*/
void	add_command_to_list(t_handle *handle, char *str)
{
	t_list	*elem;

	if (!ft_isempty(str))
	{
		if (!*(handle->is_simple_quote))
			str = replace_env_variables(handle->data, str);
		if (ft_isempty(str))
			return ;
		elem = ft_lstnew(ft_strdup(str));
		if (!elem)
			return ;
		if (!*(handle->first))
			*(handle->first) = elem;
		else
			ft_lstadd_back(handle->first, elem);
	}
}

/*
** Get the next quoted string in a command.
** @param data a pointer to a data structure.
** @param ptr a pointer to the current position in the command string.
** @param is_simple_quote a flag indicating whether
**the current quote is a single quote.
** @param command a pointer to a pointer to the command string.
** @return a pointer to the next position in the command string.
*/
static char	*get_next_quote(t_data *data, char *ptr, int is_simple_quote,
		char **command)
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
		if (quote == '"')
			ptr = replace_env_variables(data, ptr);
		if (!is_simple_quote)
			*command = replace_env_variables(data, *command);
		if (tmp != ptr)
			*command = ft_strjoin(*command, ptr);
		tmp++;
		size = ft_strlen(*command);
		*command = ft_strjoin(*command, tmp);
	}
	return (*command + size);
}

/*
** Handle special characters: '>', '<' and '|'.
** @param ptr a pointer to the current character in the command string.
** @param handle a pointer to a t_handle structure containing the necessary data.
** @return a pointer to the next character in the command string.
*/
char	*handle_special_chars(char *ptr, t_handle *handle)
{
	char	*tmp;
	char	c;

	tmp = ptr;
	c = *ptr;
	*(ptr) = '\0';
	add_command_to_list(handle, *(handle->command));
	*ptr = c;
	while (*ptr == '>' || *ptr == '<' || *ptr == '|')
		ptr++;
	c = *ptr;
	*(ptr) = '\0';
	add_command_to_list(handle, tmp);
	*(ptr) = c;
	*(handle->is_simple_quote) = 0;
	*(handle->command) = ptr;
	return (ptr);
}

/*
** Handle spaces in the command string.
** @param ptr a pointer to the current character in the command string.
** @param handle a pointer to a t_handle structure containing the necessary data.
** @return a pointer to the next character in the command string.
*/
char	*handle_spaces(char *ptr, t_handle *handle)
{
	while (ft_is_space(*ptr))
		ptr++;
	*(ptr - 1) = '\0';
	add_command_to_list(handle, *(handle->command));
	*(handle->is_simple_quote) = 0;
	*(handle->command) = ptr;
	return (ptr);
}

/*
** Handle quotes in the command string.
** @param data a pointer to a data structure.
** @param ptr a pointer to the current character in the command string.
** @param command a pointer to a pointer to the command string.
** @param is_simple_quote a pointer to a flag indicating whether
** the current quote is a single quote.
** @return a pointer to the next character in the command string.
*/
char	*handle_quotes(t_data *data, char *ptr, char **command,
		int *is_simple_quote)
{
	char	c;

	c = *ptr;
	ptr = get_next_quote(data, ptr, *is_simple_quote, command);
	if (c == '\'')
		*is_simple_quote = 1;
	return (ptr);
}

/*
** Split a command into a linked list of commands.
** @param data a pointer to a data structure.
** @param command a string containing the command to split.
** @return a pointer to the linked list of commands.
*/
t_list	*split_command(t_data *data, char *command)
{
	t_list		*first;
	char		*ptr;
	int			is_simple_quote;
	t_handle	handle;

	first = NULL;
	ptr = command;
	is_simple_quote = 0;
	handle.data = data;
	handle.first = &first;
	handle.command = &command;
	handle.is_simple_quote = &is_simple_quote;
	while (ptr && *ptr)
	{
		if (*ptr == '>' || *ptr == '<' || *ptr == '|')
			ptr = handle_special_chars(ptr, &handle);
		else if (ft_is_space(*ptr))
			ptr = handle_spaces(ptr, &handle);
		else if (ft_is_quote(*ptr))
			ptr = handle_quotes(data, ptr, &command, &is_simple_quote);
		else
			ptr++;
	}
	add_command_to_list(&handle, command);
	return (first);
}
