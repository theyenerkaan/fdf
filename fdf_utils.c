/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/12 20:30:05 by yenyilma         ###   ########.fr       */
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
void	set_menu(void *mlx)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "keys and functions", x, y);
	mlx_put_string(mlx, "Colour\t\t\t\t\t\t\t\tc", x, y += 35);
	mlx_put_string(mlx, "Zoom\t\t\t\t\t\t\t\t\t\tmouse scroll or -+", x, y += 20);
	mlx_put_string(mlx, "Translate\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(mlx, "Scale z\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate x\t\t\t\t\t\tx + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate y\t\t\t\t\t\ty + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate z\t\t\t\t\t\tz + </>", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 30);
	mlx_put_string(mlx, "Angle x\t\t\t\t\t\t\tq + </>", x, y += 25);
	mlx_put_string(mlx, "Angle y\t\t\t\t\t\t\tw + </>", x, y += 20);
	mlx_put_string(mlx, "Isometric\t\t\t\t\t1", x, y += 20);
	mlx_put_string(mlx, "Dimetric\t\t\t\t\t\t2", x, y += 20);
	mlx_put_string(mlx, "Trimetric\t\t\t\t\t3", x, y += 20);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\t0", x, y += 30);
}
