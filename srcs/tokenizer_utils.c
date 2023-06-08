/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:23:15 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/08 20:31:54 by samy             ###   ########.fr       */
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

static int	check_after_redirec(char *str, int is_special)
{
	int	error;

	error = 0;
	if (str == 0)
		error = 258;
	if (!is_special)
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
	int				is_special;

	str = NULL;
	is_special = 1;
	if ((*elem)->next != NULL)
	{
		is_special = (*elem)->next->is_special;
		str = (*elem)->next->content;
	}
	redirec = check_redirec_token(*elem);
	if (redirec != 0)
	{
		*new = ft_lstnewtoken(redirec, str);
		redirec = 1;
		if (*new == NULL)
			return (42);
		free((*elem)->content);
		if (check_after_redirec(str, is_special) == 258)
			return (258);
		*elem = (*elem)->next;
	}
	return (redirec);
}
