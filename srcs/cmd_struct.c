/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:37:34 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/08 17:13:07 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*ft_lstnewcmd(void)
{
	t_parse	*new_lst;

	new_lst = malloc(sizeof(t_parse));
	if (!new_lst)
		return (0);
	new_lst->arg_nb = 0;
	new_lst->in = 0;
	new_lst->out = 0;
	new_lst->pipe_in = 0;
	new_lst->pipe_out = 0;
	new_lst->pid = malloc(sizeof(pid_t));
	if (!new_lst->pid)
		return (0);
	*new_lst->pid = -1;
	new_lst->cmd = 0;
	new_lst->next = 0;
	return (new_lst);
}

static t_parse	*ft_lstlastcmd(t_parse *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstaddcmd_back(t_parse **lst, t_parse *new)
{
	t_parse	*last;

	if (*lst)
	{
		last = ft_lstlastcmd(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
