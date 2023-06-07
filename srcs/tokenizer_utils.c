/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:23:15 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/07 15:54:25 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	syntax_error(int error, char *str)
{
	if (error == 258)
	{
		ft_putstr_fd(PROMPT, 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		if (!str)
			str = "newline";
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
}

static int	check_after_redirec(t_split_elem *elem)
{
	int		error;
	char	*str;

	error = 0;
	str = NULL;
	if (elem && elem->content)
		str = elem->content;
	if (!elem || !elem->content)
	{
		syntax_error(258, str);
		return (258);
	}
	if (!elem->is_special)
		return (0);
	else if (ft_strcmp(str, "|") == 0)
		error = 258;
	else if (ft_strcmp(str, "<<") == 0)
		error = 258;
	else if (ft_strcmp(str, ">>") == 0)
		error = 258;
	else if (!ft_strcmp(str, "<") || !ft_strcmp(str, ">"))
		error = 258;
	syntax_error(error, str);
	return (error);
}

static int	check_redirec_token(t_split_elem *elem)
{
	if (elem->is_special == 0)
		return (0);
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

int	redirec_tokenizer(t_split_elem **elem, t_token **new)
{
	int				redirec;
	char			*str;
	t_split_elem	*next;

	str = NULL;
	if ((*elem)->next != NULL)
	{
		next = (*elem)->next;
		str = next->content;
	}
	redirec = check_redirec_token(*elem);
	if (redirec != 0)
	{
		*new = ft_lstnewtoken(redirec, str);
		redirec = 1;
		if (*new == NULL)
			return (42);
		free((*elem)->content);
		if (check_after_redirec(next) == 258)
			return (258);
		*elem = (*elem)->next;
	}
	return (redirec);
}
