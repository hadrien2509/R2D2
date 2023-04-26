/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:16:53 by sde-smed          #+#    #+#             */
/*   Updated: 2023/04/26 11:56:20 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_overflow(long long result, const char *str)
{
	if(result > LLONG_MAX / 10)
		return (1);
	if(result == LLONG_MAX / 10 && *str - '0' > LLONG_MAX % 10)
		return (1);
	return (0);
}

/*
** Converts a string to a long long integer.
** @param str the string to convert
** @param result a pointer to the result of the conversion
** @return a pointer to the result if successful, NULL otherwise
*/
long long int	*ft_atoi_long_long(const char *str, long long int *result)
{
	int	sign;

	if (!str || !result)
		return (NULL);
	*result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (check_overflow(*result, str))
			return (NULL);
		*result = *result * 10 + (*str - '0');
		str++;
	}
	*result *= sign;
	if (*result < LLONG_MIN || *result > LLONG_MAX)
		return (NULL);
	return (result);
}
