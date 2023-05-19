/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:38:29 by hgeissle          #+#    #+#             */
/*   Updated: 2023/05/19 11:41:52 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// LEAKS
t_Token	*ft_lstnewtoken(int type, char *value)
{
	t_Token	*new_lst;

	new_lst = malloc(sizeof(t_Token));
	if (!new_lst)
		return (0);
	new_lst->type = type;
	new_lst->value = value;
	new_lst->arg_nb = 0;
	new_lst->next = 0;
	return (new_lst);
}

t_Token	*ft_lstlasttoken(t_Token *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddtoken_back(t_Token **lst, t_Token *new)
{
	t_Token	*last;

	if (*lst)
	{
		last = ft_lstlasttoken(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
