/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:53 by samy              #+#    #+#             */
/*   Updated: 2022/11/30 11:56:53 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		size;

	str = (char *)s;
	size = 0;
	while (str[size])
		size++;
	while (size >= 0)
	{
		if (str[size] == (unsigned char)c)
			return (&str[size]);
		size--;
	}
	return (0);
}
