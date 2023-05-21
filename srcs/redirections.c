/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:43:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/21 14:05:56 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirec(t_parse *parse)
{
	char	*line;

	while (parse->out->next)
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
	return (0);
}
