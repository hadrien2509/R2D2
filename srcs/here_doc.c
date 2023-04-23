/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:15:44 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/23 21:00:36 by samy             ###   ########.fr       */
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
