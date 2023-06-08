/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:58:19 by samy              #+#    #+#             */
/*   Updated: 2023/06/08 12:44:23 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_command(t_handle *handle, char *str, int is_special)
{
	t_split_elem	*elem;

	if (!str)
		str = ft_strdup("");
	elem = ft_lst_split_new(ft_strdup(str), is_special);
	if (!elem)
		return (42);
	if (!*(handle->first))
		*(handle->first) = elem;
	else
		ft_lst_split_add_back(handle->first, elem);
	return (0);
}

char	*handle_special_chars(char *ptr, t_handle *handle)
{
	char	*tmp;
	char	c;

	tmp = ptr;
	c = *ptr;
	*(ptr) = '\0';
	if (!ft_isempty(handle->command))
		add_command(handle, handle->command, 0);
	*ptr = c;
	ptr++;
	if (c != '|' && *ptr == c)
		ptr++;
	c = *ptr;
	*(ptr) = '\0';
	if (!ft_isempty(tmp))
		add_command(handle, tmp, 1);
	*(ptr) = c;
	tmp = handle->command;
	handle->command = ft_strdup(ptr);
	free(tmp);
	return (handle->command);
}

char	*handle_spaces(char *ptr, t_handle *handle)
{
	char	*old_command;

	*ptr = 0;
	ptr++;
	while (ft_is_space(*ptr))
		ptr++;
	*(ptr - 1) = '\0';
	if (!ft_isempty(handle->command))
		add_command(handle, handle->command, 0);
	old_command = handle->command;
	handle->command = ft_strdup(ptr);
	free(old_command);
	return (handle->command);
}

void	init_handle(t_handle *handle, t_data *data, t_split_elem **first,
		char *command)
{
	handle->data = data;
	handle->first = first;
	handle->command = ft_strdup(command);
}

char	*add_empty(t_handle *handle, char *ptr)
{
	char	*old_command;
	char	c;

	c = *ptr;
	*ptr = '\0';
	if (ft_isempty(handle->command) && (!c || ft_is_space(c)))
	{
		old_command = handle->command;
		add_command(handle, handle->command, 0);
		*ptr = c;
		handle->command = ft_strdup(ptr);
		free(old_command);
		return (handle->command);
	}
	*ptr = c;
	return (ptr);
}
