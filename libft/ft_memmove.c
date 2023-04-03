/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:32:52 by samy              #+#    #+#             */
/*   Updated: 2022/10/11 16:18:33 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dst && !src)
		return (0);
	i = -1;
	s = (char *)src;
	d = (char *)dst;
	if (s < d)
		while (len-- > 0)
			d[len] = s[len];
	else
		while (++i < len)
			d[i] = s[i];
	return (dst);
}
