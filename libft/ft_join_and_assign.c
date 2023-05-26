/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_and_asSign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:34:37 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/26 13:00:32 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_join_and_assign(char **result, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	return (1);
}
