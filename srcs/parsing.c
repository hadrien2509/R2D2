/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:45:07 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/08 15:00:57 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_cmd_array(t_parse **new, t_parse **cmd, t_token *token, int *i)
{
	if (token->type == 0)
	{
		(*new)->cmd = malloc(sizeof(char *) * (token->arg_nb + 2));
		if (!(*new)->cmd)
			return (-1);
		(*new)->cmd[token->arg_nb + 1] = NULL;
		(*new)->cmd[++(*i)] = token->value;
	}
	else if (token->type == 1)
		(*new)->cmd[++(*i)] = token->value;
	else if (token->type == 4)
	{
		ft_lstaddcmd_back(cmd, *new);
		*new = ft_lstnewcmd();
		if (!(*new))
			return (-1);
		*i = -1;
	}
	return (0);
}

t_parse	*parse_command(t_token *token)
{
	t_parse	*new;
	t_parse	*cmd;
	int		i;
	int		check;

	i = -1;
	cmd = 0;
	new = ft_lstnewcmd();
	if (!new)
		return (NULL);
	while (token)
	{
		check = init_cmd_array(&new, &cmd, token, &i);
		if (check == -1)
			return (NULL);
		token = token->next;
	}
	ft_lstaddcmd_back(&cmd, new);
	return (cmd);
}

void	set_pipes(t_parse *cmd)
{
	int	end[2];

	pipe(end);
	cmd->pipe_out = end[1];
	cmd = cmd->next;
	cmd->pipe_in = end[0];
}

int	parse_fd(t_token *token, t_parse *cmd, t_data *data)
{
	t_parse_fd_data	fd_data;

	init_parse_fd_data(&fd_data, cmd, token);
	while (fd_data.token)
	{
		if (parse_fd_token(fd_data.token, &fd_data, data))
			return (1);
		if (fd_data.token->type == 2 || fd_data.token->type == 3
			|| fd_data.token->type == 6 || fd_data.token->type == 4)
			free(fd_data.token->value);
		fd_data.token = fd_data.token->next;
	}
	fd_data.cmd->in = fd_data.in;
	fd_data.cmd->out = fd_data.out;
	return (fd_data.error);
}
