/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:36:52 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/19 10:56:32 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// LEAKS dans le malloc
t_Inout	*ft_lstnewinout(t_Inout *prev)
{
	t_Inout	*new_inout;

	new_inout = malloc(sizeof(t_Inout));
	if (!new_inout)
		return (0);
	new_inout->fd = 0;
	new_inout->next = 0;
	new_inout->prev = prev;
	return (new_inout);
}

t_Inout	*ft_lstlastinout(t_Inout *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddinout_back(t_Inout **lst, t_Inout *new)
{
	t_Inout	*last;

	if (*lst)
	{
		last = ft_lstlastinout(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
