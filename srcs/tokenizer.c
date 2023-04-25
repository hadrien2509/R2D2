/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:03:11 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/25 13:53:31 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirec_tokenizer(t_list *elem, t_Token **new)
{
	if (ft_strcmp(elem->content, "<<") == 0)
	{
		elem = elem->next;
		*new = ft_lstnewtoken(5, elem->content);
	}
	else if (ft_strcmp(elem->content, ">>") == 0)
	{
		elem = elem->next;
		*new = ft_lstnewtoken(6, elem->content);
	}
	else if (ft_strcmp(elem->content, "<") == 0)
	{
		elem = elem->next;
		*new = ft_lstnewtoken(2, elem->content);
	}
	else if (ft_strcmp(elem->content, ">") == 0)
	{
		elem = elem->next;
		*new = ft_lstnewtoken(3, elem->content);
	}
}

void	cmd_pipes_tokenizer(t_list *elem, t_Token **new, t_data *data)
{
	static t_Token	*cmd;
	static int		arg_need;

	if (ft_strcmp(elem->content, "|") == 0)
	{
		*new = ft_lstnewtoken(4, elem->content);
		arg_need = 0;
	}
	else if (arg_need == 1)
	{
		*new = ft_lstnewtoken(1, elem->content);
		cmd->arg_nb++;
	}
	else
	{
		*new = ft_lstnewtoken(0, get_cmd_path(elem->content, data));
		arg_need = 1;
		cmd = *new;
	}
}

t_Token	create_tokens(t_list *elem, t_data *data)
{
	int		arg_needed;
	t_Token	*new;
	t_Token	*token;

	token = 0;
	arg_needed = 0;
	while (elem)
	{
		redirec_tokenizer(elem, &new);
		cmd_pipes_tokenizer(elem, &new, data);
		//printf("ok\n");
		elem = elem->next;
		ft_lstaddtoken_back(&token, new);
	}
	return (*token);
}
