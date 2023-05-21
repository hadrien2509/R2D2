/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:45:07 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/21 14:47:09 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_cmd_array(t_parse **new, t_parse **cmd, t_Token *token, int *i)
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
		ft_lstadd_back(cmd, *new);
		*new = ft_lstnewcmd();
		if (!(*new))
			return (-1);
		*i = -1;
	}
	return (0);
}

t_parse	*parse_command(t_Token *token)
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
	ft_lstadd_back(&cmd, new);
	return (cmd);
}

int	create_file(t_Inout **new, t_Inout **inout, t_Token *token)
{
	char	*name;

	name = token->value;
	if (token->type == 2)
	{
		*new = ft_lstnewinout(*new);
		(*new)->fd = open(name, O_RDONLY);
		if ((*new)->fd == -1)
		{
			perror(name);
			return (-1);
		}
		(*new)->value = name;
		ft_lstaddinout_back(inout, *new);
	}
	else if (token->type == 3)
	{
		*new = ft_lstnewinout(*new);
		(*new)->fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*new)->fd == -1)
		{
			perror(name);
			return (-1);
		}
		(*new)->value = name;
		ft_lstaddinout_back(inout, *new);
	}
	else
	{
		*new = ft_lstnewinout(*new);
		(*new)->fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if ((*new)->fd == -1)
		{
			perror(name);
			return (-1);
		}
		(*new)->value = name;
		ft_lstaddinout_back(inout, *new);
	}
	return (0);
}

void	set_pipes(t_Inout **new, t_parse *cmd, t_Inout **in, t_Inout **out)
{
	int	end[2];

	pipe(end);
	*new = ft_lstnewinout(*new);
	(*new)->fd = end[1];
	ft_lstaddinout_back(out, *new);
	cmd->out = *out;
	cmd->in = *in;
	*in = 0;
	*out = 0;
	*new = ft_lstnewinout(*new);
	(*new)->fd = end[0];
	ft_lstaddinout_back(in, *new);
}

int	parse_fd(t_Token *token, t_parse *cmd, t_data *data)
{
	t_Inout	*new;
	t_Inout	*in;
	t_Inout	*out;

	in = 0;
	out = 0;
	cmd->in = 0;
	cmd->out = 0;
	while (token)
	{
		if (token->type == 2)
		{
			if (create_file(&new, &in, token))
				return (1);
		}
		if (token->type == 3 || token->type == 6)
			create_file(&new, &out, token);
		else if (token->type == 5)
			data->exit_status = create_heredoc(&new, &in, token);
		else if (token->type == 4)
		{
			set_pipes(&new, cmd, &in, &out);
			cmd = cmd->next;
		}
		if (data->exit_status == 130)
			return (0);
		token = token->next;
	}
	cmd->in = in;
	cmd->out = out;
	return (0);
}