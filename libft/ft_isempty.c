/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:53:55 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/24 09:53:57 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isempty(char *str)
{
	while (str && *str)
	{
		if (!ft_is_space(*str))
			return (0);
		str++;
	}
	return (1);
}
