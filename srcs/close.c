/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:47:47 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/05 18:48:06 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fd(t_parse *parse)
{
	if (parse->pipe_in)
		close(parse->pipe_in);
	if (parse->pipe_out)
		close(parse->pipe_out);
	while (parse->in)
	{
		close(parse->in->fd);
		parse->in = parse->in->next;
	}
	while (parse->out)
	{
		close(parse->out->fd);
		parse->out = parse->out->next;
	}
}
