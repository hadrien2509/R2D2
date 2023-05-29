/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:23:15 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/29 11:48:30 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	syntax_error(int error, char *str)
{
	if (error == 258)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (!str)
			str = "newline";
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
}

static int	check_after_redirec(void *str)
{
	int	error;

	error = 0;
	if (str == 0)
		error = 258;
	else if (ft_strcmp(str, "|") == 0)
	{
		str = "|";
		error = 258;
	}
	else if (ft_strcmp(str, "<<") == 0)
	{
		str = "<<";
		error = 258;
	}
	else if (ft_strcmp(str, ">>") == 0)
	{
		str = ">>";
		error = 258;
	}
	else if (!ft_strcmp(str, "<") && !ft_strcmp(str, ">"))
		error = 258;
	syntax_error(error, str);
	return (error);
}

int	check_redirec_token(t_list *elem)
{
	if (ft_strcmp(elem->content, "<<") == 0)
		return (5);
	else if (ft_strcmp(elem->content, ">>") == 0)
		return (6);
	else if (ft_strcmp(elem->content, "<") == 0)
		return (2);
	else if (ft_strcmp(elem->content, ">") == 0)
		return (3);
	return (0);
}

int	redirec_tokenizer(t_list **elem, t_token **new)
{
	int		redirec;
	char	*str;

	str = NULL;
	if ((*elem)->next != NULL)
		str = (*elem)->next->content;
	redirec = check_redirec_token(*elem);
	if (redirec != 0)
	{
		*new = ft_lstnewtoken(redirec, str);
		if (*new == NULL)
			return (42);
		free((*elem)->content);
		*elem = (*elem)->next;
		if (check_after_redirec(str) == 258)
			return (258);
	}
	return (redirec);
}
