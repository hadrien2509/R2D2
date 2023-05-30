/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:37:34 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/30 11:25:39 by sde-smed         ###   ########.fr       */
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
