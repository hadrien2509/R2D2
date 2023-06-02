/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:58:19 by samy              #+#    #+#             */
/*   Updated: 2023/06/02 15:00:23 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_command_to_list(t_handle *handle, char *str, int is_pipe)
{
	t_list	*elem;

	if (!ft_isempty(str) || is_pipe)
	{
		elem = ft_lstnew(ft_strdup(str));
		if (!elem)
			return (42);
		if (!*(handle->first))
			*(handle->first) = elem;
		else
			ft_lstadd_back(handle->first, elem);
	}
	return (0);
}

char	*handle_special_chars(char *ptr, t_handle *handle)
{
	char	*tmp;
	char	c;
	int		result;

	tmp = ptr;
	c = *ptr;
	*(ptr) = '\0';
	result = add_command_to_list(handle, handle->command, 0);
	if (result)
		return (NULL);
	*ptr = c;
	ptr++;
	if (c != '|' && *ptr == c)
		ptr++;
	c = *ptr;
	*(ptr) = '\0';
	result = add_command_to_list(handle, tmp, 0);
	if (result)
		return (NULL);
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
	add_command_to_list(handle, handle->command, 0);
	old_command = handle->command;
	handle->command = ft_strdup(ptr);
	free(old_command);
	return (handle->command);
}

void	init_handle(t_handle *handle, t_data *data, t_list **first,
		char *command)
{
	handle->data = data;
	handle->first = first;
	handle->command = ft_strdup(command);
}
