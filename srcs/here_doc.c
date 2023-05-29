/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:15:44 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/29 23:36:56 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_process(t_in_out *new)
{
	char	*line;
	size_t	len;
	int		cmp;

	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(ERROR);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			exit(1);
		len = ft_strlen(line) - 1;
		cmp = ft_strncmp(line, new->value, len);
		if (len == ft_strlen(new->value) && !cmp)
			break ;
		write(new->fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	exit(0);
}

static int	here_doc(t_in_out *new)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		heredoc_process(new);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(ERROR);
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(ERROR);
	close(new->fd);
	return (status);
}

int	create_heredoc(t_in_out **new, t_in_out **in, t_token *token)
{
	int	end[2];
	int	status;

	pipe(end);
	*new = ft_lstnewinout(*new);
	(*new)->fd = end[1];
	(*new)->value = token->value;
	status = here_doc(*new);
	close(end[1]);
	if (status == 130)
		return (130);
	(*new)->fd = end[0];
	ft_lstaddinout_back(in, *new);
	return (0);
}
