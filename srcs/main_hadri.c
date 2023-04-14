/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/14 16:05:02 by hgeissle         ###   ########.fr       */
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
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	curr;
	struct termios	save;
	t_data			data;
	t_Token			token;
	t_Parse			parse;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &curr);
	tcgetattr(STDIN_FILENO, &save);
	curr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &curr);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (ERROR);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (ERROR);
	if (init_data(&data, envp))
		return (ERROR);
	while (1)
	{
		data.line = readline(PROMPT);
		if (!data.line)
		{
			printf("exit\n");
			return (0);
		}
		add_history(data.line);
		data.command = ft_split(data.line, ' ');
		token = create_tokens(data.command);
		parse_command(&token, &parse);
		parse_fd(&token, &parse);
		execline(&parse);
		// if (check_command(data.command, &data))
		// 	printf("an error append\n");
		free(data.line);
	}
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}