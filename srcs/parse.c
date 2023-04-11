/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:45:43 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/11 17:26:51 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
t_Parse	*ft_lstnewcmd(int arg_nb)
{
	t_Parse	*new_lst;

	new_lst = malloc(sizeof(t_Parse));
	if (!new_lst)
		return (0);
	new_lst->arg_nb = 0;
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

t_Token	create_tokens(char **line)
{
	int			i;
	int			arg_needed;
	t_Token		*new;
	t_Token		*token;
	t_Parse		*parse;
	t_Parse		*new_cmd;

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
			ft_lstaddcmd_back(&parse, new_cmd);
			arg_needed = 0;
		}
		else if (arg_needed == 1)
		{
			new = ft_lstnewtoken(1, line[i]);
			new_cmd->arg_nb++;
		}
		else
		{
			new = ft_lstnewtoken(0, get_cmd_path(line[i]));
			new = ft_lstnewcmd(0);
			arg_needed = 1;
		}
		i++;
		ft_lstaddtoken_back(&token, new);
	}
	ft_lstaddcmd_back(&parse, new);
	return (*token);
}

void	parse_tokens(t_Token *token, t_Parse *parse)
{
	int		i;

	i = 0;
	parse->cmd = malloc(sizeof(char *) * (parse->arg_nb + 2));
	if (!parse->cmd)
		return (0);
	while (token->type != 0)
	{
		if (token->type == 0 || token->type == 1)
			parse->cmd[i++] = token->value;
		if (token->type == 2)
		{
			parse->stdin = open(token->value, O_RDONLY);
			if (parse->stdin == -1)
				perror(token->value);
		}
		if (token->type == 3)
		{
			parse->stdout = open(token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (parse->stdout == -1)
				perror(token->value);
		}
		if (token->type == 4)
			parse->stdout = pipe(end);
		token = token->next;
	}
}
