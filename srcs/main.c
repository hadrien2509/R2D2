/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:29:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/23 21:01:17 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			status;

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

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

//print the list
void	print_list(t_list *list)
{
	while (list)
	{
		printf("[%s]\n", (char *)list->content);
		list = list->next;
	}
}

//is_empty, check if a char * is empty
int	is_empty(char *str)
{
	while (str && *str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

int	add_to_list(t_data *data, t_list **list, char *str, int is_simple_quote)
{
	t_list	*elem;

	if (!is_empty(str))
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

	first = NULL;
	ptr = command;
	while (ptr && *ptr)
	{
		is_simple_quote = 0;
		if (is_space(*ptr))
		{
			while (is_space(*ptr))
				ptr++;
			*(ptr - 1) = '\0';
			add_to_list(data, &first, command, 0);
			command = ptr;
		}
		else if (is_quote(*ptr))
		{
			*ptr = '\0';
			add_to_list(data, &first, command, 0);
			command = ++ptr;
			while (!is_quote(*ptr))
				ptr++;
			if (*ptr == '\'')
				is_simple_quote = 1;
			*ptr = '\0';
			add_to_list(data, &first, command, is_simple_quote);
			command = ++ptr;
		}
		else
			ptr++;
	}
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
		data.command = ft_split(data.line, ' ');
		//print_list(split_command(&data, data.line));
		//if (ft_nb_split(data.command) > 0)
		add_history(data.line);
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
