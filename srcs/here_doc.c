/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_Doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:15:44 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/19 17:36:01 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_Inout *new)
{
	size_t	len;
	char	*line;

	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
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
