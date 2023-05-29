/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:03:11 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/29 12:44:56 by sde-smed         ###   ########.fr       */
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
