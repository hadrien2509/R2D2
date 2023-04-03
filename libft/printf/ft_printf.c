/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:51:21 by samy              #+#    #+#             */
/*   Updated: 2022/12/20 12:05:39 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"

static int	format(va_list args, const char *str, int *count)
{
	int	nb_char;

	if (*str == 'd' || *str == 'i')
		nb_char = ft_putnbr(va_arg(args, int));
	else if (*str == 'u')
		nb_char = ft_putnbr_ul(va_arg(args, unsigned int));
	else if (*str == 'c')
		nb_char = ft_putchar(va_arg(args, int));
	else if (*str == 'p')
		nb_char = print_address(va_arg(args, unsigned long));
	else if (*str == 's')
		nb_char = ft_putstr(va_arg(args, char *));
	else if (*str == 'x')
		nb_char = print_hex(va_arg(args, unsigned int), 'x');
	else if (*str == 'X')
		nb_char = print_hex(va_arg(args, unsigned int), 'X');
	else
		nb_char = ft_putchar(*str);
	if (nb_char == -1)
		*count = -1;
	else
		*count += nb_char;
	return (*count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count = format(args, str, &count);
		}
		else
			count += ft_putchar(*str);
		if (count == -1)
			return (-1);
		str++;
	}
	va_end(args);
	return (count);
}
