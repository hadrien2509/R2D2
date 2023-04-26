/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:37:34 by hgeissle          #+#    #+#             */
/*   Updated: 2023/04/26 12:08:41 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_Parse	*ft_lstnewcmd(void)
{
	t_Parse	*new_lst;

	new_lst = malloc(sizeof(t_Parse));
	if (!new_lst)
		return (0);
	new_lst->arg_nb = 0;
	new_lst->in = 0;
	new_lst->out = 0;
	new_lst->cmd = 0;
	new_lst->next = 0;
	return (new_lst);
}

t_Parse	*ft_lstlastcmd(t_Parse *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddcmd_back(t_Parse **lst, t_Parse *new)
{
	t_Parse	*last;

	if (*lst)
	{
		last = ft_lstlastcmd(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
