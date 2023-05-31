/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:45:49 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/31 14:47:32 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_exit_status = 1;
}

void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}
