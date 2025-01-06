/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:38:01 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/06 20:39:39 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
