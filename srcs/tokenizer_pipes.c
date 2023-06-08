/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:41:40 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/08 14:20:36 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_after_pipe(t_data *data, t_split_elem **elem)
{
	int	error;

	error = 0;
	if ((*elem)->is_first)
	{
		print_error(0, "syntax error near unexpected token `|'", 0, 258);
		error = 258;
	}
	if ((*elem)->next == 0)
		error = complete_pipe(data, elem);
	if ((*elem)->next && ft_strcmp((*elem)->next->content, "|") == 0)
		error = 258;
	syntax_error(error, "|");
	return (error);
}

static int	create_pipe_token(t_token **new, int *arg_need, t_split_elem **elem)
{
	free((*elem)->content);
	*new = ft_lstnewtoken(4, NULL);
	if (*new == NULL)
		return (42);
	*arg_need = 0;
	return (0);
}

static int	create_argument_token(t_token **new, t_split_elem **elem,
		t_token *cmd)
{
	*new = ft_lstnewtoken(1, (*elem)->content);
	if (*new == NULL)
		return (42);
	cmd->arg_nb++;
	return (0);
}

static int	create_command_token(t_token **new, char *content, int *arg_need)
{
	*new = ft_lstnewtoken(0, content);
	if (*new == NULL)
		return (42);
	*arg_need = 1;
	return (0);
}

int	cmd_pipes_tokenizer(t_split_elem **elem, t_token **new, t_data *data,
		int *arg_need)
{
	static t_token	*cmd;
	int				check;

	if (ft_strcmp((*elem)->content, "|") == 0 && (*elem)->is_special)
	{
		if (create_pipe_token(new, arg_need, elem) == 42)
			return (42);
		check = check_after_pipe(data, elem);
		if (check == 258 || check == 130)
			return (check);
	}
	else if (*arg_need == 1)
	{
		check = create_argument_token(new, elem, cmd);
		if (check == 42 || check == 127)
			return (check);
	}
	else if (*arg_need == 0)
	{
		check = create_command_token(new, (*elem)->content, arg_need);
		cmd = *new;
		if (check)
			return (check);
	}
	return (0);
}
