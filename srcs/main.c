/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/26 13:01:19 by samy             ###   ########.fr       */
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

void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

void	init_signal(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(print_error("error", "handle signal failed", NULL, 1));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(print_error("error", "ignore signal failed", NULL, 1));
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	curr;
	struct termios	save;
	t_data			data;
	t_token			*token;
	t_parse			*parse;

	data.envtab = envp;
	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &curr);
	tcgetattr(STDIN_FILENO, &save);
	curr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &curr);
	if (init_data(&data, envp))
		return (print_error("error", "init_data failed", NULL, 1));
	while (1)
	{
		data.line = readline(PROMPT);
		if (!data.line)
		{
			printf("exit\n");
			return (0);
		}
		if (!ft_isempty(data.line))
			add_history(data.line);
		token = 0;
		data.split = split_command(&data, data.line);
		data.exit_status = create_tokens(&data, &token);
		if (data.exit_status == 0)
		{
			parse = parse_command(token);
			if (!parse)
				exit(1);
		}
		if (data.exit_status == 0)
			data.exit_status = parse_fd(token, parse, &data);
		if (data.exit_status == 0)
			exec_line(parse, &data);
		free(data.line);
		if (data.exit_status == 42)
			exit(1);
	}
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}
