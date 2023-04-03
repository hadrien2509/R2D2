/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/03/31 19:07:06 by hgeissle         ###   ########.fr       */
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
	else if (signal == SIGQUIT)
		return ;
}

int	main(void)
{
	char	*line;

	while (1)
	{
		if (signal(SIGINT, signal_handler) == SIG_ERR)
			return (ERROR);
		if (signal(SIGQUIT, signal_handler) == SIG_ERR)
			return (ERROR);
		line = readline("minishell-1.0$ ");
		if (!line)
			return (0);
		free(line);
	}
	return (0);
}
