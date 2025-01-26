/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:38:01 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 08:55:57 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_map(const char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (len < 5)
		return (0);
	mapname += len - 4;
	return (ft_strncmp(mapname, ".fdf", 4) == 0);
}

void	error_exit(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
	exit(1);
}

void	error_map(int fd, t_map *map, const char *msg)
{
	close(fd);
	free(map);
	error_exit(msg);
}
