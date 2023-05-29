/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:36:52 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/30 00:57:39 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_in_out	*ft_lstnewinout(t_in_out *prev)
{
	t_in_out	*new_inout;

	new_inout = malloc(sizeof(t_in_out));
	if (!new_inout)
		return (0);
	new_inout->fd = 0;
	new_inout->value = 0;
	new_inout->next = 0;
	new_inout->prev = prev;
	return (new_inout);
}

t_in_out	*ft_lstlastinout(t_in_out *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddinout_back(t_in_out **lst, t_in_out *new)
{
	t_in_out	*last;

	if (*lst)
	{
		last = ft_lstlastinout(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
