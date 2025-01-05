/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:58:31 by yenyilma          #+#    #+#             */
/*   Updated: 2024/11/14 00:58:32 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (!dest && !src)
		return (dest);
	if (dest <= src)
		return (ft_memcpy(dest, src, len));
	else
	{
		while (len--)
		{
			((char *)dest)[len] = ((char *)src)[len];
		}
	}
	return (dest);
}
