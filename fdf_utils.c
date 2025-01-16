/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/16 19:54:04 by yenyilma         ###   ########.fr       */
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

void	ft_free_split(void **split, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(t_map *map)
{
    int	i;

    if (!map)
        return ;
    if (map->mgrid)
    {
        i = 0;
        while (i < map->rows)
        {
            free(map->mgrid[i]);
            i++;
        }
        free(map->mgrid);
    }
    if (map->grid)
    {
        i = 0;
        while (i < map->rows)
        {
            free(map->grid[i]);
            i++;
        }
        free(map->grid);
    }
    free(map);
}
void	set_menu(void *mlx, void *win)
{
    int		x;
    int		y;

    x = 20;
    y = 20;
    mlx_string_put(mlx, win, x, y, 0xFFFFFF, "keys and functions");
    mlx_string_put(mlx, win, x, y += 35, 0xFFFFFF, "Colour\t\t\t\t\t\t\t\tc");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Zoom\t\t\t\t\t\t\t\t\t\tmouse scroll or -+");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Translate\t\t\t\t\tarrow keys");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Scale z\t\t\t\t\t\t\ts + </>");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Rotate x\t\t\t\t\t\tx + </>");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Rotate y\t\t\t\t\t\ty + </>");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Rotate z\t\t\t\t\t\tz + </>");
    mlx_string_put(mlx, win, x, y += 30, 0xFFFFFF, "PROJECTION");
    mlx_string_put(mlx, win, x, y += 25, 0xFFFFFF, "Angle x\t\t\t\t\t\t\tq + </>");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Angle y\t\t\t\t\t\t\tw + </>");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Isometric\t\t\t\t\t1");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Dimetric\t\t\t\t\t\t2");
    mlx_string_put(mlx, win, x, y += 20, 0xFFFFFF, "Trimetric\t\t\t\t\t3");
    mlx_string_put(mlx, win, x, y += 30, 0xFFFFFF, "RESET\t\t\t\t\t\t\t\t\t0");
}
