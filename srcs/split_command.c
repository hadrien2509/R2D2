/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:41:13 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/28 11:14:44 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_to_list(t_data *data, t_list **list, char *str, int is_simple_quote)
{
	t_list	*elem;

	if (!ft_isempty(str))
	{
		if (!is_simple_quote)
			str = replace_env_variables(data, str);
		if (ft_isempty(str))
			return;
		elem = ft_lstnew(ft_strdup(str));
		if (!elem)
			return;
		if (!*list)
			*list = elem;
		else
			ft_lstadd_back(list, elem);
	}
	return;
}

static char *get_next_quote(t_data *data, char *ptr, int is_simple_quote, char **command)
{
	char	quote;
	char	*tmp;

	quote = *ptr;
	*ptr = '\0';
	tmp = ++ptr;
	while (*tmp && *tmp != quote)
		tmp++;
	if (*tmp == quote)
	{
		*tmp = '\0';
		if(quote == '"')
			ptr = replace_env_variables(data, ptr);
		if (!is_simple_quote)
			*command = replace_env_variables(data, *command);
		if (tmp == ptr)
			ptr++;
		tmp++;
		*command = ft_strjoin(*command, ptr);
	}
	return (tmp);
}

t_list	*split_command(t_data *data, char *command)
{
	char	*ptr;
	char	c;
	t_list	*first;
	int		is_simple_quote;

	first = NULL;
	ptr = command;
		is_simple_quote = 0;
	while (ptr && *ptr)
	{
		if (ft_is_space(*ptr))
		{
			while (ft_is_space(*ptr))
				ptr++;
			*(ptr - 1) = '\0';
			add_to_list(data, &first, command, is_simple_quote);
			is_simple_quote = 0;
			command = ptr;
		}
		else if (ft_is_quote(*ptr))
		{
			c = *ptr;
			ptr = get_next_quote(data, ptr, is_simple_quote, &command);
			if (c == '\'')
				is_simple_quote = 1;
		}
		else
			ptr++;
	}
	if (ft_is_quote(*(ptr - 1)))
		*(ptr - 1) = '\0';
	if (*command)
		add_to_list(data, &first, command, is_simple_quote);
	return (first);
}
