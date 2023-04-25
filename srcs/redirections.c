/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:43:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/24 13:44:23 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
