/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:03:11 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/30 11:41:19 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_child(t_pipe_data *data)
{
	int			i;

	i = 0;
	write(1, "> ", 2);
	if (signal(SIGINT, &signal_handler_child) == SIG_ERR)
		exit(ERROR);
	data->str = get_next_line(0);
	if (!data->str)
		exit (-1);
	data->len = ft_strlen(data->str);
	data->str_nonl = malloc(sizeof(char) * data->len);
	if (!data->str_nonl)
		exit (-1);
	data->str_nonl[data->len - 1] = '\0';
	while (data->str[i] != '\n' && data->str[i])
	{
		data->str_nonl[i] = data->str[i];
		i++;
	}
	ft_putstr_fd(data->str_nonl, data->end[1]);
	close(data->end[1]);
	close(data->end[0]);
	exit(data->status);
}


int	complete_pipe(t_list **elem)
{
	t_list		*new;
	t_pipe_data	data;
	int			pid;

	data.status = 0;
	pipe(data.end);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		exec_child(&data);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	if (waitpid(pid, &data.status, 0) == -1)
		return (1);
	close(data.end[1]);
	data.str = get_next_line(data.end[0]);
	close(data.end[0]);
	if (!data.str)
		return (data.status);
	new = ft_lstnew(data.str);
	ft_lstadd_back(elem, new);
	return (data.status);
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
		if (check == 127 || check == 258 || check == 42)
			return (check);
		if (check == 130)
			return (1);
		elem = elem->next;
		ft_lstaddtoken_back(token, new);
	}
	ft_lstclear(&elem, *del);
	return (0);
}
