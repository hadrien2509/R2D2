/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:45:43 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/10 10:07:01 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	set_cmd(char **line, int i, t_instructions *lst)
// {
// 	if (i = )
// }

void	create_tokens(char **line, t_instructions *lst)
{
	t_Token	*token;
	int		i;
	int		arg_needed;

	i = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], "<") == 0)
		{
			i++;
			token->type = 2;
			token->value = line[i];
		}
		if (ft_strcmp(line[i], ">") == 0)
		{
			i++;
			token->type = 3;
			token->value = line[i];
		}
		if (arg_needed == 1)
		{
			token->type = 1;
			token->value = line[i];
		}
		else
		{
			token->type = 0;
			if (strchr(line[i], '/') != NULL)
				token->value = strdup(line[i]);
			else
				token->value = get_binary_path(line[i]);
			if (!token->value)
				exit(1);
			if (access(token->value, F_OK) != 0)
			{
				free(token->value);
				exit(1);
			}
			arg_needed = 1;
		}
	}
}

void	create_tokens(char **line, t_instructions *lst)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], ">") == 0)
		{
			ft_setcmd();
			ft_setcmdarg();
			ft_setinput();
			ft_setoutput();
		}
		if (ft_strcmp(line[i], "<") == 0)
		{
			ft_setcmd();
			ft_setcmdarg();
			ft_setinput();
			ft_setoutput();
		}
		if (ft_strcmp(line[i], "") == 0)
			break;
	}
}
