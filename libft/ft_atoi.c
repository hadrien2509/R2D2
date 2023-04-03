/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:04:13 by samy              #+#    #+#             */
/*   Updated: 2022/12/20 12:17:22 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	max_size(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long	nb;
	long		sign;
	int			i;
	int			cpt;

	cpt = 1;
	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i++] - '0';
		if (cpt++ > 19 || nb < 0)
		{
			return (max_size(sign));
		}
	}
	return ((int)(nb * sign));
}
