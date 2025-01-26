/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 16:49:05 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_atoi_base(const char *nptr, const char *base)
{
	int	neg;
	int	result;
	int	nbase;	

	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r')
		nptr++;
	neg = 1;
	if (*nptr == '-')
	{
		neg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	nbase = ft_strlen(base);
	result = 0;
	while (nptr && *nptr && ft_strchr(base, *nptr))
	{
		result = result * nbase + ft_strchr(base, *nptr) - base;
		nptr++;
	}
	return (neg * result);
}
