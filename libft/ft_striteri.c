/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:31 by samy              #+#    #+#             */
/*   Updated: 2022/10/12 10:50:55 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	char			*str;
	unsigned int	i;

	if (!s)
		return ;
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		(*f)(i, &str[i]);
		i++;
	}
}
