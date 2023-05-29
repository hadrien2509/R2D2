/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:58:19 by samy              #+#    #+#             */
/*   Updated: 2023/05/29 11:00:09 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_command_to_list(t_handle *handle, char *str)
{
	t_list	*elem;

	if (!ft_isempty(str))
	{
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

char	*handle_special_chars(char *ptr, t_handle *handle)
{
	char	*tmp;
	char	c;

	tmp = ptr;
	c = *ptr;
	*(ptr) = '\0';
	add_command_to_list(handle, handle->command);
	*ptr = c;
	ptr++;
	if (c != '|' && *ptr == c)
		ptr++;
	c = *ptr;
	*(ptr) = '\0';
	add_command_to_list(handle, tmp);
	*(ptr) = c;
	tmp = handle->command;
	handle->command = ft_strdup(ptr);
	free(tmp);
	return (handle->command);
}

char	*handle_spaces(char *ptr, t_handle *handle)
{
	char	*old_command;

	while (ft_is_space(*ptr))
		ptr++;
	*(ptr - 1) = '\0';
	add_command_to_list(handle, handle->command);
	old_command = handle->command;
	handle->command = ft_strdup(ptr);
	free(old_command);
	return (handle->command);
}
