/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:43:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/25 14:51:26 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirec(t_Parse *parse)
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
}
