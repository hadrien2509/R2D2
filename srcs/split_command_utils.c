/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:58:19 by samy              #+#    #+#             */
/*   Updated: 2023/05/15 13:50:41 by sde-smed         ###   ########.fr       */
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
	ptr++;
	if (c != '|' && *ptr == c)
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
