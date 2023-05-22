/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:45:07 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/22 10:48:26 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_cmd_array(t_parse **new, t_parse **cmd, t_Token *token, int *i)
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
	ft_lstaddcmd_back(&cmd, new);
	return (cmd);
}

static int	create_file(t_Inout **new, t_Inout **inout, t_Token *token)
{
	if (token->type == 2)
	{
		*new = ft_lstnewinout(*new);
		(*new)->fd = open(token->value, O_RDONLY);
		(*new)->value = token->value;
		ft_lstaddinout_back(inout, *new);
	}
	else if (token->type == 3)
	{
		*new = ft_lstnewinout(*new);
		(*new)->fd = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		(*new)->value = token->value;
		ft_lstaddinout_back(inout, *new);
	}
	else
	{
		*new = ft_lstnewinout(*new);
		(*new)->fd = open(token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		(*new)->value = token->value;
		ft_lstaddinout_back(inout, *new);
	}
	if ((*new)->fd == -1)
		perror(token->value);
	return ((*new)->fd);
}

static void	set_pipes(t_Inout **new, t_parse *cmd, t_Inout **in, t_Inout **out)
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

int	parse_fd(t_Token *token, t_parse *cmd)
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
			if (create_file(&new, &in, token) == -1)
				return (1);
		}
		else if (token->type == 3 || token->type == 6)
		{
			if (create_file(&new, &out, token) == -1)
				return (1);
		}
		else if (token->type == 5)
		{
			if (create_heredoc(&new, &in, token) == 130)
				return (130);
		}
		else if (token->type == 4)
		{
			set_pipes(&new, cmd, &in, &out);
			cmd = cmd->next;
		}
		token = token->next;
	}
	cmd->in = in;
	cmd->out = out;
	return (0);
}
