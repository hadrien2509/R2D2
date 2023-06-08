/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:37:36 by samy              #+#    #+#             */
/*   Updated: 2023/06/08 14:56:13 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse_fd_data	*init_parse_fd_data(t_parse_fd_data *fd_data, t_parse *cmd,
		t_token *token)
{
	fd_data->new = 0;
	fd_data->in = 0;
	fd_data->out = 0;
	fd_data->error = 0;
	cmd->in = 0;
	cmd->out = 0;
	fd_data->cmd = cmd;
	fd_data->token = token;
	return (fd_data);
}

static void	parse_fd_type_4(t_parse_fd_data *fd_data)
{
	fd_data->error = 0;
	set_pipes(fd_data->cmd);
	fd_data->cmd->in = fd_data->in;
	fd_data->cmd->out = fd_data->out;
	fd_data->in = 0;
	fd_data->out = 0;
	fd_data->cmd = fd_data->cmd->next;
}

int	create_file(t_in_out **new, t_in_out **inout, t_token *token)
{
	if (token->type == 2)
	{
		*new = ft_lstnewinout();
		if (!(*new))
			return (-1);
		(*new)->fd = open(token->value, O_RDONLY);
	}
	else if (token->type == 3)
	{
		*new = ft_lstnewinout();
		if (!(*new))
			return (-1);
		(*new)->fd = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		*new = ft_lstnewinout();
		if (!(*new))
			return (-1);
		(*new)->fd = open(token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	ft_lstaddinout_back(inout, *new);
	perror_prompt((*new)->fd, token->value);
	return ((*new)->fd);
}

int	parse_fd_token(t_token *token, t_parse_fd_data *fd_data, t_data *data)
{
	if (token->type == 2 && fd_data->error == 0)
	{
		if (create_file(&(fd_data->new), &fd_data->in, token) == -1)
		{
			fd_data->cmd->cmd = 0;
			data->exit_status = 1;
			fd_data->error = 1;
		}
	}
	else if ((token->type == 3 || token->type == 6) && fd_data->error == 0)
	{
		if (create_file(&(fd_data->new), &fd_data->out, token) == -1)
		{
			fd_data->cmd->cmd = 0;
			data->exit_status = 1;
			fd_data->error = 1;
		}
	}
	else if (token->type == 5)
		if (create_heredoc(data, &(fd_data->new), &fd_data->in, token) == 130)
			return (130);
	if (token->type == 4)
		parse_fd_type_4(fd_data);
	return (0);
}
