/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:16:53 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/17 13:03:28 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Converts a string to a long long integer with the given sign.
** @param str the string to convert
** @param sign the sign of the result
** @return the converted long long integer
*/
static long long	ft_str_to_long_long(const char *str, int sign)
{
	long long	result;

	result = 0;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/*
** Converts a string to a long long integer.
** @param str the string to convert
** @return the converted long long integer
*/
long long	ft_atoi_long_long(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = ft_str_to_long_long(str, sign);
	return (result);
}
