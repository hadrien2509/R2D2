/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:15:44 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/25 12:37:58 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int status; //extern int	status;

void	here_doc(t_Inout *new)
{
	size_t	len;
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (status == 130)
			break ;
		if (!line)
			exit(1);
		len = ft_strlen(line) - 1;
		if (len == ft_strlen(new->value) && !ft_strncmp(line, new->value, len))
			break ;
		write(new->fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(new->fd);
}

void	create_heredoc(t_Inout **new, t_Inout **in, t_Token *token)
{
	int		end[2];

	pipe(end);
	*new = ft_lstnewinout(*new);
	(*new)->fd = end[1];
	(*new)->value = token->value;
	here_doc(*new);
	close(end[1]);
	if (status == 130)
		return ;
	(*new)->fd = end[0];
	ft_lstaddinout_back(in, *new);
}
