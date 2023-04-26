/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:03:11 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/26 09:27:50 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

int	check_after_redirec(void *str)
{
	int	error;

	error = 0;
	if (str == 0)
		error = 258;
	else if (ft_strcmp(str, "|") == 0)
		error = 258;
	else if (ft_strcmp(str, "<<") == 0)
		error = 258;
	else if (ft_strcmp(str, ">>") == 0)
		error = 258;
	else if (ft_strcmp(str, "<") == 0)
		error = 258;
	else if (ft_strcmp(str, ">") == 0)
		error = 258;
	if (error == 258)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'", 2);
		return (258);
	}
	return (0);
}

int	redirec_tokenizer(t_list **elem, t_Token **new)
{
	int	redirec;

	redirec = 1;
	if (ft_strcmp((*elem)->content, "<<") == 0)
		*new = ft_lstnewtoken(5, (*elem)->next->content);
	else if (ft_strcmp((*elem)->content, ">>") == 0)
		*new = ft_lstnewtoken(6, (*elem)->next->content);
	else if (ft_strcmp((*elem)->content, "<") == 0)
		*new = ft_lstnewtoken(2, (*elem)->next->content);
	else if (ft_strcmp((*elem)->content, ">") == 0)
		*new = ft_lstnewtoken(3, (*elem)->next->content);
	else
		redirec = 0;
	if (redirec == 1)
	{
		(*elem) = (*elem)->next;
		if (check_after_redirec((*elem)->content) == 258)
			return (258);
	}
	return (redirec);
}

int	complete_pipe(t_list **elem)
{
	t_list	*new;

	write(1, "\n> ", 1);
	new = ft_lstnew(get_next_line(0));
	if (status == 130)
		return (130);
	ft_lstadd_back(elem, new);
	return (0);
}
int	check_after_pipe(t_list **elem)
{
	int		error;

	error = 0;
	if ((*elem)->next == 0)
		error = complete_pipe(elem);
	else if (ft_strcmp((*elem)->content, "|") == 0)
		error = 258;
	else if (ft_strcmp((*elem)->content, "<<") == 0)
		error = 258;
	else if (ft_strcmp((*elem)->content, ">>") == 0)
		error = 258;
	else if (ft_strcmp((*elem)->content, "<") == 0)
		error = 258;
	else if (ft_strcmp((*elem)->content, ">") == 0)
		error = 258;
	if (error == 258)
		ft_putstr_fd("syntax error near unexpected token `|'", 2);
	return (error);
}

int	cmd_pipes_tokenizer(t_list **elem, t_Token **new, t_data *data, int *arg_need)
{
	static t_Token	*cmd;

	if (ft_strcmp((*elem)->content, "|") == 0)
	{
		*new = ft_lstnewtoken(4, (*elem)->content);
		*arg_need = 0;
		if (check_after_pipe(elem) == 1)
			return (1);
	}
	else if (*arg_need == 1)
	{
		*new = ft_lstnewtoken(1, (*elem)->content);
		cmd->arg_nb++;
	}
	else
	{
		*new = ft_lstnewtoken(0, get_cmd_path((*elem)->content, data));
		*arg_need = 1;
		cmd = *new;
	}
	return (0);
}

int	create_tokens(t_list *elem, t_data *data, t_Token **token)
{
	t_Token	*new;
	int		check;
	int		arg_need;

	*token = 0;
	arg_need = 0;
	while (elem)
	{
		check = redirec_tokenizer(&elem, &new);
		if (check == 258)
			return (258);
		if (check == 0)
			check = cmd_pipes_tokenizer(&elem, &new, data, &arg_need);
		if (check == 130)
			return (1);
		elem = elem->next;
		ft_lstaddtoken_back(token, new);
	}
	return (0);
}
