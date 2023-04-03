/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:36:42 by samy              #+#    #+#             */
/*   Updated: 2022/12/20 12:05:50 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_address(unsigned long nb)
{
	int	count;
	int	nb_char;

	if (nb == 0)
		return (ft_putstr("0x0"));
	count = ft_putstr("0x");
	if (count == -1)
		return (-1);
	nb_char = put_hexa(nb, "0123456789abcdef");
	if (nb_char == -1)
		return (-1);
	return (count + nb_char);
}

int	print_hex(unsigned int nb, const char format)
{
	if (nb == 0)
		return (write(1, "0", 1));
	if (format == 'x')
		return (put_hexa(nb, "0123456789abcdef"));
	return (put_hexa(nb, "0123456789ABCDEF"));
}
