/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:40:53 by samy              #+#    #+#             */
/*   Updated: 2023/06/08 14:12:21 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_split_elem	*ft_lst_split_clear(t_split_elem *lst)
{
	t_split_elem	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

t_split_elem	*ft_lst_split_add_back(t_split_elem **alst, t_split_elem *new)
{
	t_split_elem	*elem;

	if (!alst || !new)
		return (NULL);
	if (!*alst)
	{
		*alst = new;
		return (*alst);
	}
	elem = *alst;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	return (*alst);
}

t_split_elem	*ft_lst_split_new(char *value, int is_special)
{
	t_split_elem	*elem;

	elem = malloc(sizeof(t_split_elem));
	if (!elem)
		return (NULL);
	elem->content = value;
	elem->is_special = is_special;
	elem->is_first = 0;
	elem->next = NULL;
	return (elem);
}
