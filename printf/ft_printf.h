/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:15:49 by yenyilma          #+#    #+#             */
/*   Updated: 2024/10/22 17:32:27 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *string, ...);
int		ft_putchar(char a);
int		ft_putnbr(int n);
int		ft_putstr(char *s, int count);
int		ft_puthex(unsigned long long n, char *hex);
int		ft_putnbr_for_unsigned(unsigned int n);

#endif
