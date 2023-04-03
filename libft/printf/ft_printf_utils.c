/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:55:47 by samy              #+#    #+#             */
/*   Updated: 2022/12/20 12:05:46 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(char c)
{
	return (write (1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	size;

	size = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[size])
		size++;
	return (write(1, s, size));
}

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nb < 0)
	{
		count = ft_putchar('-');
		if (count == -1)
			return (-1);
		nb = -nb;
	}
		count += ft_putnbr_ul(nb);
	if (count <= 0)
		return (-1);
	return (count);
}

int	ft_putnbr_ul(unsigned long nb)
{
	int	nb_char;
	int	count;

	count = 0;
	if (nb >= 10)
	{
		nb_char = ft_putnbr_ul(nb / 10);
		if (nb_char == -1)
			return (-1);
		count += nb_char;
		nb_char = ft_putchar(nb % 10 + '0');
	}
	else
		nb_char = ft_putchar(nb + '0');
	if (nb_char == -1)
		return (-1);
	count += nb_char;
	return (count);
}

int	put_hexa(unsigned long nb, char *base)
{
	int	count;
	int	nb_char;

	count = 0;
	if (nb < 16)
		nb_char = write(1, &base[nb], 1);
	else
	{
		count = put_hexa(nb / 16, base);
		if (count == -1)
			return (-1);
		nb_char = write(1, &base[nb % 16], 1);
		if (nb_char == -1)
			return (-1);
	}
	return (count + nb_char);
}
