/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/05 18:44:43 by hgeissle         ###   ########.fr       */
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

static void	prompt_line(t_data *data)
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
		quit(data, 0);
	}
	if (!ft_isempty(data->line))
		add_history(data->line);
	data->split = split_command(data, data->line);
	free(data->line);
}

static void	del(void *elem_to_del)
{
	t_list	*elem;

	elem = (t_list *)elem_to_del;
	if (elem)
		free(elem);
}

static void	shell(t_data *data, t_token *token, t_parse *parse)
{
	prompt_line(data);
	token = 0;
	data->family = 0;
	if (data->split)
	{
		data->exit_status = create_tokens(data, &token);
		if (data->exit_status != 42 && data->exit_status != 258)
		{
			parse = parse_command(token);
			if (!parse)
				quit(data, 1);
		}
		if (data->exit_status != 42 && data->exit_status != 258)
			data->exit_status = parse_fd(token, parse, data);
		free_tokens(token);
		if (data->exit_status == 0)
			exec_line(parse, data);
		free_parse(parse);
		ft_lstclear(&data->family, *del);
		if (data->exit_status == 42)
			quit(data, print_error("error", "malloc failed", NULL, 1));
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
