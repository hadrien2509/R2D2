/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:03:11 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/27 16:12:18 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	complete_pipe(t_list **elem)
{
	t_list	*new;
	char	*str;
	char	*str_nonl;
	int		i;
	int		len;
	int		pid;
	int		status;
	int		end[2];

	i = 0;
	status = 0;
	pipe(end);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		write(1, "> ", 2);
		if (signal(SIGINT, &signal_handler_child) == SIG_ERR)
			exit(ERROR);
		str = get_next_line(0);
		if (!str)
			return (-1);
		len = ft_strlen(str);
		str_nonl = malloc(sizeof(char) * len);
		if (!str_nonl)
			return (-1);
		str_nonl[len - 1] = '\0';
		while (str[i] != '\n' && str[i])
		{
			str_nonl[i] = str[i];
			i++;
		}
		ft_putstr_fd(str_nonl, end[1]);
		close(end[1]);
		close(end[0]);
		exit(status);
	}
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(ERROR);
	if (signal(SIGINT, &signal_handler) == SIG_ERR)
		exit(ERROR);
	close(end[1]);
	str = get_next_line(end[0]);
	close(end[0]);
	if (!str)
		return (status);
	new = ft_lstnew(str);
	ft_lstadd_back(elem, new);
	return (status);
}

int	check_after_pipe(t_list **elem)
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

int	cmd_pipes_tokenizer(t_list **elem, t_token **new, t_data *data,
		int *arg_need)
{
	static t_token	*cmd;
	int				check;

	if (ft_strcmp((*elem)->content, "|") == 0)
	{
		free((*elem)->content);
		*new = ft_lstnewtoken(4, NULL);
		*arg_need = 0;
		check = check_after_pipe(elem);
		if (check == 258 || check == 130)
			return (check);
	}
	else if (*arg_need == 1)
	{
		*new = ft_lstnewtoken(1, (*elem)->content);
		cmd->arg_nb++;
	}
	else
	{
		*new = ft_lstnewtoken(0, get_cmd_path((*elem)->content, data));
		if (!(*new)->value)
			return (127);
		*arg_need = 1;
		cmd = *new;
	}
	return (0);
}

static void	del(void *elem_to_del)
{
	t_list	*elem;

	elem = (t_list *)elem_to_del;
	if (elem)
		free(elem);
}

int	create_tokens(t_data *data, t_token **token)
{
	t_token	*new;
	int		check;
	int		arg_need;
	t_list	*elem;

	*token = 0;
	arg_need = 0;
	elem = data->split;
	while (elem)
	{
		check = redirec_tokenizer(&elem, &new);
		if (check == 0)
			check = cmd_pipes_tokenizer(&elem, &new, data, &arg_need);
		if (check == 127)
			return (127);
		if (check == 130)
			return (1);
		if (check == 258)
			return (258);
		elem = elem->next;
		ft_lstaddtoken_back(token, new);
	}
	ft_lstclear(&elem, *del);
	return (0);
}
