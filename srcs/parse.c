/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:45:43 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/24 12:44:45 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	status;

int	check_builtins(char *arg)
{
	if (!ft_strcmp(arg, "pwd"))
		return (1);
	else if (!ft_strcmp(arg, "cd"))
		return (1);
	else if (!ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset"))
		return (1);
	else if (!ft_strcmp(arg, "env"))
		return (1);
	else if (!ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

char	*get_cmd_path(char *arg, t_data *data)
{
	char	*path;

	if (ft_strchr(arg, '/') != NULL)
		path = ft_strdup(arg);
	else if (check_builtins(arg))
	{
		path = ft_strdup(arg);
		return (path);
	}
	else
		path = get_binary_path(data->env, arg);
	if (path)
		path = get_absolute_path(data->env, data->pwd, path);
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
	new_lst->out = 0;
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

t_Inout	*ft_lstnewinout(t_Inout *prev)
{
	t_Inout	*new_inout;

	new_inout = malloc(sizeof(t_Inout));
	if (!new_inout)
		return (0);
	new_inout->fd = 0;
	new_inout->next = 0;
	new_inout->prev = prev;
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
		last = ft_lstlastinout(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

char	*find_env_variable(char **str)
{
	char	*result;
	char	*command;
	char	c;

	c = 0;
	command = *str;
	while (*command && (*command == '_' || ft_isalnum(*command)))
		command++;
	if (*command)
	{
		c = *command;
		*command = '\0';
	}
	result = ft_strdup(*str);
	if (c)
		*command = c;
	return (result);
}

char	*replace_env_variables(t_data *data, char *command)
{
	char	*tmp;
	char	*result;
	char	*ptr;

	result = ft_strdup("");
	ptr = ft_strchr(command, '$');
	if (!ptr)
		return (command);
	while (ptr && *ptr)
	{
		if (!*(ptr + 1))
		{
			result = ft_strjoin(result, "$");
			return (result);
		}
		*ptr = 0;
		ptr++;
		result = ft_strjoin(result, command);
		command = ptr;
		if (is_space(*ptr))
			result = ft_strjoin(result, "$");
		if (*ptr == '?')
		{
			tmp = ft_itoa(data->exit_status);
			result = ft_strjoin(result, tmp);
			command += ft_strlen(tmp);
		}
		else
		{
			tmp = find_env_variable(&ptr);
			command += ft_strlen(tmp);
			tmp = get_env(data->env, tmp);
			if (tmp)
				result = ft_strjoin(result, tmp);
		}
		ptr = ft_strchr(command, '$');
		if (!ptr)
			result = ft_strjoin(result, command);
	}
	return (result);
}

t_Token	create_tokens(t_list *elem, t_data *data)
{
	int		arg_needed;
	t_Token	*new;
	t_Token	*cmd;
	t_Token	*token;

	token = 0;
	arg_needed = 0;
	while (elem)
	{
		if (ft_strcmp(elem->content, "<<") == 0)
		{
			elem = elem->next;
			new = ft_lstnewtoken(5, elem->content);
		}
		else if (ft_strcmp(elem->content, ">>") == 0)
		{
			elem = elem->next;
			new = ft_lstnewtoken(6, elem->content);
		}
		else if (ft_strcmp(elem->content, "<") == 0)
		{
			elem = elem->next;
			new = ft_lstnewtoken(2, elem->content);
		}
		else if (ft_strcmp(elem->content, ">") == 0)
		{
			elem = elem->next;
			new = ft_lstnewtoken(3, elem->content);
		}
		else if (ft_strcmp(elem->content, "|") == 0)
		{
			new = ft_lstnewtoken(4, elem->content);
			arg_needed = 0;
		}
		else if (arg_needed == 1)
		{
			new = ft_lstnewtoken(1, elem->content);
			cmd->arg_nb++;
		}
		else
		{
			new = ft_lstnewtoken(0, get_cmd_path(elem->content, data));
			arg_needed = 1;
			cmd = new;
		}
		elem = elem->next;
		ft_lstaddtoken_back(&token, new);
	}
	return (*token);
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
		if (token->type == 0)
		{
			new->cmd = malloc(sizeof(char *) * (token->arg_nb + 2));
			if (!new->cmd)
				return (0);
			new->cmd[token->arg_nb + 1] = NULL;
			new->cmd[++i] = token->value;
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
	ft_lstaddcmd_back(&cmd, new);
	return (cmd);
}

void	parse_fd(t_Token *token, t_Parse *cmd)
{
	int		end[2];
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
			new = ft_lstnewinout(new);
			new->fd = open(token->value, O_RDONLY);
			new->value = token->value;
			ft_lstaddinout_back(&in, new);
		}
		else if (token->type == 3)
		{
			new = ft_lstnewinout(new);
			new->fd = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			new->value = token->value;
			ft_lstaddinout_back(&out, new);
		}
		else if (token->type == 5)
		{
			new = ft_lstnewinout(new);
			pipe(end);
			new->fd = end[1];
			new->value = token->value;
			here_doc(new);
			close(end[1]);
			if (status == 130)
				return ;
			new->fd = end[0];
			ft_lstaddinout_back(&in, new);
		}
		else if (token->type == 6)
		{
			new = ft_lstnewinout(new);
			new->fd = open(token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			new->value = token->value;
			ft_lstaddinout_back(&out, new);
		}
		else if (token->type == 4)
		{
			pipe(end);
			new = ft_lstnewinout(new);
			new->fd = end[1];
			ft_lstaddinout_back(&out, new);
			cmd->out = out;
			cmd->in = in;
			cmd = cmd->next;
			in = 0;
			out = 0;
			new = ft_lstnewinout(new);
			new->fd = end[0];
			ft_lstaddinout_back(&in, new);
		}
		token = token->next;
	}
	cmd->in = in;
	cmd->out = out;
}

// static void	ft_putstr_fds(char *s, t_Inout *out)
// {
// 	if (!s)
// 		return ;
// 	if (!out)
// 		write(1, s, ft_strlen(s));
// 	while (out)
// 	{
// 		write(out->fd, s, ft_strlen(s));
// 		out = out->next;
// 	}
// }

int	execute(t_Parse *parse, t_data *data, int pid)
{
	int		result;
	char	**env_list;

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		env_list = env_list_to_tab(data->env_size, data->env);
		if (execve(parse->cmd[0], parse->cmd, env_list) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	if (waitpid(pid, &result, 0) == -1)
		return (1);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(ERROR);
	return (result);
}

int	exec_cmd(t_Parse *parse, t_data *data)
{
	int	child;
	int	result;

	result = 0;
	if (!parse->in)
	{
		child = fork();
		if (child == 0)
		{
			if (parse->out)
				dup2(parse->out->fd, 1);
			result = execute(parse, data, child);
		}
		wait(&child);
	}
	while (parse->in)
	{
		child = fork();
		if (child == 0)
		{
			dup2(parse->in->fd, 0);
			if (parse->out)
				dup2(parse->out->fd, 1);
			result = execute(parse, data, child);
		}
		wait(&child);
		parse->in = parse->in->next;
	}
	if (parse->out)
		close(parse->out->fd);
	return (result);
}

// void	exec_nocmd(t_Parse *parse)
// {
// 	char	*line;

// 	while (parse->in)
// 	{
// 		line = get_next_line(parse->in->fd);
// 		while (line)
// 		{
// 			if (status == 130)
// 				return ;
// 			if (parse->out)
// 				ft_putstr_fd(line, parse->out->fd);
// 			else
// 				ft_putstr_fd(line, 1);
// 			line = get_next_line(parse->in->fd);
// 		}
// 		parse->in = parse->in->next;
// 	}
// }

void	redirec(t_Parse *parse)
{
	char	*line;

	parse->out = parse->out->next;
	while (parse->out)
	{
		parse->out->prev->fd = open(parse->out->prev->value, O_RDONLY);
		line = get_next_line(parse->out->prev->fd);
		while (line)
		{
			ft_putstr_fd(line, parse->out->fd);
			line = get_next_line(parse->out->prev->fd);
		}
		parse->out = parse->out->next;
	}
}

int	exec_builtins(t_Parse *parse, t_data *data)
{
	if (!ft_strcmp(parse->cmd[0], "pwd"))
	{
		if (parse->out)
		{
			ft_putstr_fd(data->pwd, parse->out->fd);
			write(parse->out->fd, "\n", 1);
			return (0); //Ajouter une condition ici
		}
		else
			return ((printf("%s\n", data->pwd) == 0));
	}
	else if (!ft_strcmp(parse->cmd[0], "cd"))
		return (builtin_cd(data, parse->cmd[1]));
	else if (!ft_strcmp(parse->cmd[0], "echo"))
		return (builtin_echo(parse->cmd));
	else if (!ft_strcmp(parse->cmd[0], "export"))
		return (export(data, &parse->cmd[1]));
	else if (!ft_strcmp(parse->cmd[0], "unset"))
		return (unset(data->env, &parse->cmd[1]));
	else if (!ft_strcmp(parse->cmd[0], "env"))
		return (print_env(data->env));
	else if (!ft_strcmp(parse->cmd[0], "exit"))
		return (ft_exit(data, &parse->cmd[1]));
	return (0);
}

void	exec_line(t_Parse *parse, t_data *data)
{
	while (parse)
	{
		if (parse->cmd && parse->cmd[0])
		{
			if (check_builtins(parse->cmd[0]))
				exec_builtins(parse, data);
			else
				exec_cmd(parse, data);
		}
		// else if (!parse->cmd)
		// 	exec_nocmd(parse);
		if (parse->cmd && parse->out && parse->out->next)
			redirec(parse);
		parse = parse->next;
	}
}

// void	exec(t_Parse *parse)
// {
// 	int	child;

// 	while (parse)
// 	{
// 		while (parse->cmd && parse->in)
// 		{
// 			child = fork();
// 			if (child == 0)
// 			{
// 				dup2(parse->in->fd, 0);
// 				dup2(parse->out->fd, 1);
// 				execve(parse->cmd[0], parse->cmd);
// 			}
// 			parse->in = parse->in->next;
// 		}
// 		if (!parse->cmd)
// 			ft_putstr_fds(get_next_line(0), parse->in);
// 		parse->out = parse->out->next;
// 		while (parse->out)
// 		{
// 			ft_putstr_fd(get_next_line(parse->out->prev->fd), parse->out->fd);
// 			parse->out = parse->out->next;
// 		}
// 		parse = parse->next;
// 	}
// }

// void	parse_tokens(t_Token *token, t_Parse *parse)
// {
// 	int		i;
// 	int		end[2];
// 	t_Parse	*new;

// 	i = 0;
// 	while (token->type)
// 	{
// 		new = ft_lstnewcmd();
// 		if (token->type == 0)
// 		{
// 			parse->cmd = malloc(sizeof(char *) * (token->arg_nb + 2));
// 			if (!parse->cmd)
// 				return (0);
// 			parse->cmd[parse->arg_nb + 1] = NULL;
// 			parse->cmd[i++] = token->value;
// 		}
// 		if (token->type == 1)
// 			parse->cmd[i++] = token->value;
// 		if (token->type == 2)
// 			parse
// 		if (token->type == 3)
// 			parse->out_nb++;
// 		if (token->type == 4)
// 		{
// 			pipe(end);
// 			parse->out = end[1];
// 			new = ft_lstnewcmd();
// 			ft_lstaddcmd_back(&parse, new);
// 			parse = parse->next;
// 			parse->in = end[0];
// 		}
// 		token = token->next;
// 	}
// }
