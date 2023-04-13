/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:45:43 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/13 14:53:06 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

// void	set_cmd(char **line, int i, t_instructions *lst)
// {
// 	if (i = )
// }

char	*get_cmd_path(char *arg)
{
	char	*path;

	if (ft_strchr(arg, '/') != NULL)
		path = ft_strdup(arg);
	else
		path = get_binary_path(arg);
	if (!path | (access(path, F_OK) != 0))
	{
		free(path);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (path);
}
void	print_tokens(t_Token *token)
{
	while (token)
	{
		printf("%d\n", token->type);
		printf("%s\n", token->value);
		token = token->next;
	}
}


t_Token	*ft_lstnewtoken(int type, char *value)
{
	t_Token	*new_lst;

	new_lst = malloc(sizeof(t_Token));
	if (!new_lst)
		return (0);
	new_lst->type = type;
	new_lst->value = value;
	new_lst->arg_nb = 0;
	new_lst->next = 0;
	return (new_lst);
}

t_Token	*ft_lstlasttoken(t_Token *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddtoken_back(t_Token **lst, t_Token *new)
{
	t_Token	*last;

	if (*lst)
	{
		last = ft_lstlasttoken(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
t_Parse	*ft_lstnewcmd(void)
{
	t_Parse	*new_lst;

	new_lst = malloc(sizeof(t_Parse));
	if (!new_lst)
		return (0);
	new_lst->arg_nb = 0;
	new_lst->in = 0;
	new_lst->out = 1;
	new_lst->cmd = 0;
	new_lst->next = 0;
	return (new_lst);
}

t_Parse	*ft_lstlastcmd(t_Parse *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddcmd_back(t_Parse **lst, t_Parse *new)
{
	t_Parse	*last;

	if (*lst)
	{
		last = ft_lstlastcmd(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
t_Inout	*ft_lstnewinout(void)
{
	t_Inout	*new_inout;

	new_inout = malloc(sizeof(t_Inout));
	if (!new_inout)
		return (0);
	new_inout->fd = 0;
	new_inout->next = 0;
	return (new_inout);
}

t_Inout	*ft_lstlastinout(t_Inout *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddinout_back(t_Inout **lst, t_Inout *new)
{
	t_Inout	*last;

	if (*lst)
	{
		last = ft_lstlastcmd(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_Token	create_tokens(char **line)
{
	int			i;
	int			arg_needed;
	t_Token		*new;
	t_Token		*cmd;
	t_Token		*token;

	token = 0;
	i = 0;
	arg_needed = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], "<") == 0)
		{
			i++;
			new = ft_lstnewtoken(2, line[i]);
		}
		else if (ft_strcmp(line[i], ">") == 0)
		{
			i++;
			new = ft_lstnewtoken(3, line[i]);
		}
		else if (ft_strcmp(line[i], "|") == 0)
		{
			new = ft_lstnewtoken(4, line[i]);
			arg_needed = 0;
		}
		else if (arg_needed == 1)
		{
			new = ft_lstnewtoken(1, line[i]);
			cmd->arg_nb++;
		}
		else
		{
			new = ft_lstnewtoken(0, get_cmd_path(line[i]));
			arg_needed = 1;
			cmd = new;
		}
		i++;
		ft_lstaddtoken_back(&token, new);
	}
	return (*token);
}

void	parse_command(t_Token *token, t_Parse *cmd)
{
	t_Parse	*new;
	int		i;

	i = -1;
	new = ft_lstnewcmd();
	while (token)
	{
		if (token->type == 0)
		{
			new->cmd = malloc(sizeof(char *) * (token->arg_nb + 2));
			if (!new->cmd)
				return (0);
			new->cmd[parse->arg_nb + 1] = NULL;
			new->cmd[i++] = token->value;
		}
		else if (token->type == 1)
			new->cmd[++i] = token->value;
		else if (token->type == 4)
		{
			ft_lstaddcmd_back(&cmd, new);
			new = ft_lstnewcmd();
			i = -1;
		}
		token = token->next;
	}
}

void	parse_fd(t_Token *token, t_Parse *cmd)
{
	int		end[2];
	t_In	*new_in;
	t_Out	*new_out;
	t_In	*in;
	t_Out	*out;

	in = 0;
	out = 0;
	while (token)
	{
		if (token->type == 2)
		{
			new_in = ft_lstnewinout();
			new_in->fd = open(token->value, O_RDONLY);
			ft_lstaddinout_back(&in, new_in);
		}
		else if (token->type == 3)
		{
			new_out = ft_lstnewinout();
			new_out->fd = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			ft_lstaddinout_back(&out, new_out);
		}
		else if (token->type == 4)
		{
			pipe(end);
			new_out = ft_lstnewinout();
			new_out->fd = end[1];
			ft_lstaddinout_back(&out, new_out);
			cmd->out = out;
			cmd = cmd->next;
			in = 0;
			out = 0;
			new_in = ft_lstnewinout();
			new_in->fd = end[0];
			ft_lstaddinout_back(&out, new_in);
		}
	}
}

void	exec(t_Parse *cmd)
{
	int	child;

	while (parse)
	{
		while (parse->in)
		{
			child = fork();
			if (child == 0)
			{
				dup2(parse->in->fd, 0);
				dup2(parse->out->fd, 1);
				execve(parse->cmd[0], parse->cmd);
			}
			parse = parse->in->next;
		}
		parse->out = parse->out->next;
		while (parse->out)
		{
			get_next_line(parse->out->prev->fd);
			parse->out = parse->out->next;
		}
		parse = parse->next;
	}
}

void	parse_tokens(t_Token *token, t_Parse *parse)
{
	int		i;
	int		end[2];
	t_Parse	*new;

	i = 0;
	while (token->type)
	{
		new = ft_lstnewcmd();
		if (token->type == 0)
		{
			parse->cmd = malloc(sizeof(char *) * (token->arg_nb + 2));
			if (!parse->cmd)
				return (0);
			parse->cmd[parse->arg_nb + 1] = NULL;
			parse->cmd[i++] = token->value;
		}
		if (token->type == 1)
			parse->cmd[i++] = token->value;
		if (token->type == 2)
			parse
		if (token->type == 3)
			parse->out_nb++;
		if (token->type == 4)
		{
			pipe(end);
			parse->out = end[1];
			new = ft_lstnewcmd();
			ft_lstaddcmd_back(&parse, new);
			parse = parse->next;
			parse->in = end[0];
		}
		token = token->next;
	}
}
