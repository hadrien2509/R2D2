/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:11:51 by sde-smed          #+#    #+#             */
/*   Updated: 2022/10/06 16:16:10 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	cpy = malloc((i + 1) * sizeof(char));
	if (!cpy)
		return (0);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
