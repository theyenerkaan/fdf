/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:50:35 by yenyilma          #+#    #+#             */
/*   Updated: 2024/10/22 17:32:12 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parser(const char string, va_list args)
{
	int	count;

	count = 0;
	if (string == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (string == 's')
		count = ft_putstr(va_arg(args, char *), count);
	else if (string == 'p')
	{
		count += write(1, "0x", 2);
		count += ft_puthex(va_arg(args, unsigned long long),
				"0123456789abcdef");
	}
	else if (string == 'd' || string == 'i')
		count = ft_putnbr(va_arg(args, int));
	else if (string == 'u')
		count = ft_putnbr_for_unsigned(va_arg(args, unsigned int));
	else if (string == 'x')
		count = ft_puthex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (string == 'X')
		count = ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (string == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] != '%')
			count += ft_putchar(string[i]);
		else
		{
			i++;
			count += ft_parser(string[i], args);
		}
		i++;
	}
	va_end(args);
	return (count);
}
