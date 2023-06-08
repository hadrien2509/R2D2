/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:38:29 by hgeissle          #+#    #+#             */
/*   Updated: 2023/06/08 13:11:29 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_lstnewtoken(int type, char *value)
{
	t_token	*new_lst;

	new_lst = malloc(sizeof(t_token));
	if (!new_lst)
		return (0);
	new_lst->type = type;
	new_lst->value = value;
	new_lst->arg_nb = 0;
	new_lst->next = 0;
	return (new_lst);
}

static t_token	*ft_lstlasttoken(t_token *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstaddtoken_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (*lst)
	{
		last = ft_lstlasttoken(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
