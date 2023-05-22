/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_and_asign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:34:37 by sde-smed          #+#    #+#             */
/*   Updated: 2023/05/22 10:34:59 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_join_and_asign(char **result, char *str)
{
	*result = ft_strjoin(*result, str);
	if (!*result)
		return (0);
	return (1);
}
