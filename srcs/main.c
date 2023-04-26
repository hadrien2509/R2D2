/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/26 15:19:49 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		status;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		status = 130;
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
	t_Token			*token;
	t_Parse			*parse;

	data.envtab = envp;
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
		//if (ft_nb_split(data.command) > 0)
		add_history(data.line);
		token = 0;
		data.split = split_command(&data, data.line);
		data.exit_status = create_tokens(&data, &token);
		parse = parse_command(token);
		parse_fd(token, parse, &data);
		if (status != 130)
		{
			exec_line(parse, &data);
			printf("ok\n");
		}
		free(data.line);
	}
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}
