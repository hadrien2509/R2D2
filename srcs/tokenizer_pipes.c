/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:41:40 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/29 13:09:42 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_after_pipe(t_list **elem)
{
	int	error;

	error = 0;
	if ((*elem)->next == 0)
		error = complete_pipe(elem);
	if ((*elem)->next && ft_strcmp((*elem)->next->content, "|") == 0)
		error = 258;
	syntax_error(error, "|");
	return (error);
}

static int	create_pipe_token(t_token **new, int *arg_need)
{
	*new = ft_lstnewtoken(4, NULL);
	if (*new == NULL)
		return (42);
	*arg_need = 0;
	return (0);
}

static int	create_argument_token(t_token **new, t_list **elem, t_token *cmd)
{
	*new = ft_lstnewtoken(1, (*elem)->content);
	if (*new == NULL)
		return (42);
	cmd->arg_nb++;
	return (0);
}

static int	create_command_token(t_token **new, char *content, t_data *data,
		int *arg_need)
{
	*new = ft_lstnewtoken(0, get_cmd_path(content, data));
	if (*new == NULL)
		return (42);
	if ((*new)->value == NULL)
		return (127);
	*arg_need = 1;
	return (0);
}

int	cmd_pipes_tokenizer(t_list **elem, t_token **new, t_data *data,
		int *arg_need)
{
	static t_token	*cmd;
	int				check;

	if (ft_strcmp((*elem)->content, "|") == 0)
	{
		free((*elem)->content);
		if (create_pipe_token(new, arg_need) == 42)
			return (42);
		check = check_after_pipe(elem);
		if (check == 258 || check == 130)
			return (check);
	}
	else if (*arg_need == 1)
	{
		if (create_argument_token(new, elem, cmd) == 42)
			return (42);
	}
	else
	{
		check = create_command_token(new, (*elem)->content, data, arg_need);
		if (check)
			return (check);
		cmd = *new;
	}
	return (0);
}
