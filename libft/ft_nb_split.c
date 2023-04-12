/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:50:23 by samy              #+#    #+#             */
/*   Updated: 2023/04/12 17:51:15 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts the number of elements in a null-terminated array of strings.
** @param split the array of strings to count
** @return the number of elements in the array
*/
int	ft_nb_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}
