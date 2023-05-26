/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:23:15 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/26 16:19:00 by hgeissle         ###   ########.fr       */
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

int	redirec_tokenizer(t_list **elem, t_token **new)
{
	int		redirec;
	char	*str;

	str = 0;
	if ((*elem)->next)
		str = (*elem)->next->content;
	redirec = 1;
	if (ft_strcmp((*elem)->content, "<<") == 0)
		*new = ft_lstnewtoken(5, str);
	else if (ft_strcmp((*elem)->content, ">>") == 0)
		*new = ft_lstnewtoken(6, str);
	else if (ft_strcmp((*elem)->content, "<") == 0)
		*new = ft_lstnewtoken(2, str);
	else if (ft_strcmp((*elem)->content, ">") == 0)
		*new = ft_lstnewtoken(3, str);
	else
		redirec = 0;
	if (redirec == 1)
	{
		free((*elem)->content);
		(*elem) = (*elem)->next;
		if (check_after_redirec(str) == 258)
			return (258);
	}
	return (redirec);
}
