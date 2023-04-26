/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:45:07 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/26 16:01:57 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

int	init_cmd_array(t_Parse **new, t_Parse **cmd, t_Token *token, int *i)
{
	if (token->type == 0)
	{
		(*new)->cmd = malloc(sizeof(char *) * (token->arg_nb + 2));
		if (!(*new)->cmd)
			return (42);
		(*new)->cmd[token->arg_nb + 1] = NULL;
		(*new)->cmd[++(*i)] = token->value;
	}
	else if (token->type == 1)
		(*new)->cmd[++(*i)] = token->value;
	else if (token->type == 4)
	{
		ft_lstaddcmd_back(cmd, *new);
		*new = ft_lstnewcmd();
		*i = -1;
	}
	return (0);
}

t_Parse	*parse_command(t_Token *token)
{
	t_Parse	*new;
	t_Parse	*cmd;
	int		i;

	i = -1;
	cmd = 0;
	new = ft_lstnewcmd();
	while (token)
	{
		init_cmd_array(&new, &cmd, token, &i);
		token = token->next;
	}
	ft_lstaddcmd_back(&cmd, new);
	return (cmd);
}

void	create_file(t_Inout	**new, t_Inout **inout, t_Token *token)
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
}

void	set_pipes(t_Inout	**new, t_Parse **cmd, t_Inout **in, t_Inout **out)
{
	int			end[2];

	pipe(end);
	*new = ft_lstnewinout(*new);
	(*new)->fd = end[1];
	ft_lstaddinout_back(out, *new);
	(*cmd)->out = *out;
	(*cmd)->in = *in;
	*cmd = (*cmd)->next;
	*in = 0;
	*out = 0;
	*new = ft_lstnewinout(*new);
	(*new)->fd = end[0];
	printf("%d\n", (*new)->fd);
	ft_lstaddinout_back(in, *new);
}

void	parse_fd(t_Token *token, t_Parse *cmd, t_data *data)
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
		if (token->type == 2 || token->type == 3 || token->type == 6)
			create_file(&new, &in, token);
		else if (token->type == 5)
			data->exit_status = create_heredoc(&new, &in, token);
		else if (token->type == 4)
			set_pipes(&new, &cmd, &in, &out);
		if (data->exit_status == 130)
			return ;
		token = token->next;
	}
	cmd->in = in;
	cmd->out = out;
}
