/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/09 13:24:17 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_signal(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(print_error("error", "handle signal failed", NULL, 1));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(print_error("error", "ignore signal failed", NULL, 1));
}

static int	prompt_line(t_data *data)
{
	data->line = readline(PROMPT);
	if (g_exit_status == 1)
	{
		data->exit_status = g_exit_status;
		g_exit_status = 0;
	}
	if (!data->line)
	{
		printf("exit\n");
		quit(data, data->old_exit_status);
	}
	if (!ft_isempty(data->line))
	{
		add_history(data->line);
		data->split = split_command(data, data->line);
		free(data->line);
		return (0);
	}
	return (1);
}

static void	shell(t_data *data, t_token *token, t_parse *parse)
{
	int	res;

	if (prompt_line(data))
		return ;
	data->old_exit_status = data->exit_status;
	token = 0;
	if (data->split)
	{
		res = create_tokens(data, &token);
		if (res != 42 && res != 258 && res != 1)
		{
			parse = parse_command(token);
			if (!parse)
				quit(data, 1);
		}
		if (res != 42 && res != 258 && res != 1)
			res = parse_fd(token, parse, data);
		free_tokens(token);
		if (res == 0)
			exec_line(parse, parse, data);
		free_parse(parse);
		if (res == 42)
			quit(data, print_error("error", "malloc failed", NULL, 1));
		data->exit_status = res;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	curr;
	struct termios	save;
	t_data			data;
	t_token			*token;
	t_parse			*parse;

	(void)argc;
	(void)argv;
	data.envtab = envp;
	tcgetattr(STDIN_FILENO, &curr);
	tcgetattr(STDIN_FILENO, &save);
	curr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &curr);
	init_signal();
	if (init_data(&data, envp))
		return (print_error("error", "init_data failed", NULL, 1));
	token = NULL;
	parse = NULL;
	g_exit_status = 0;
	while (1)
		shell(&data, token, parse);
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}
