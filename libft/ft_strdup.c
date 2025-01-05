/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:23:27 by yenyilma          #+#    #+#             */
/*   Updated: 2024/11/14 01:04:25 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	length;
	int		i;

	i = 0;
	length = ft_strlen(s1) + 1;
	ptr = (char *) malloc (sizeof(char) * length);
	if (!ptr)
		return (NULL);
	while (length)
	{
		ptr[i] = s1[i];
		i++;
		length--;
	}
	return (ptr);
}
