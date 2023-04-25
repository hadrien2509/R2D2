/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/25 12:54:07 by hgeissle         ###   ########.fr       */
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

void	print_list(t_list *list)
{
	while (list)
	{
		printf("[%s]\n", (char *)list->content);
		list = list->next;
	}
}

int	add_to_list(t_data *data, t_list **list, char *str, int is_simple_quote)
{
	t_list	*elem;

	if (!ft_isempty(str))
	{
		if (!is_simple_quote)
			str = replace_env_variables(data, str);
		elem = ft_lstnew(ft_strdup(str));
		if (!elem)
			return (1);
		if (!*list)
			*list = elem;
		else
			ft_lstadd_back(list, elem);
		return (0);
	}
	return (0);
}

t_list	*split_command(t_data *data, char *command)
{
	char	*ptr;
	t_list	*first;
	int		is_simple_quote;
	int		there_is_quote;

	there_is_quote = 1;
	first = NULL;
	ptr = command;
	is_simple_quote = 0;
	while (ptr && *ptr)
	{
		if (ft_is_space(*ptr))
		{
			while (ft_is_space(*ptr))
				ptr++;
			*(ptr - 1) = '\0';
			add_to_list(data, &first, command, is_simple_quote);
			command = ptr;
		}
		else if (ft_is_quote(*ptr))
		{
			is_simple_quote = (*ptr == '\'');
			*ptr = '\0';
			if (((ptr - 1) && !ft_is_space(*(ptr - 1))))
			{
				*ptr = '\0';
				if (there_is_quote % 2)
					command = replace_env_variables(data, command);
				ptr = ft_strjoin(command, ptr + 1);
				command = ptr;
				there_is_quote++;
			}
			else if ((!(ptr + 1) || ft_is_space(*(ptr + 1))))
			{
				if (*(ptr + 1))
				{
					*ptr = '\0';
					add_to_list(data, &first, command, is_simple_quote);
					command = ++ptr;
				}
				there_is_quote++;
			}
		}
		else
			ptr++;
	}
	if (command)
		add_to_list(data, &first, command, is_simple_quote);
	return (first);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	curr;
	struct termios	save;
	t_data			data;
	t_Token			token;
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
		//data.command = ft_split(data.line, ' ');
		//if (ft_nb_split(data.command) > 0)
		add_history(data.line);
		//print_list(split_command(&data, data.line));
		//exit(0);
		token = create_tokens(split_command(&data, data.line), &data);
		parse = parse_command(&token);
		parse_fd(&token, parse);
		if (status != 130)
			exec_line(parse, &data);
		free(data.line);
	}
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}
