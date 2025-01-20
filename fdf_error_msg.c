/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:38:01 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/20 09:01:44 by yenyilma         ###   ########.fr       */
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
void	draw_background(t_fdf *base, int color)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = base->addr + (y * base->line_len + x * (base->bpp / 8));
			*(unsigned int *)dst = color; 
			x++;
		}
		y++;
	}
}

void	projection(t_map *map, int y, int x)
{
	t_mpoint	*point;
	t_mpoint	tmp;
	t_point		*projection;

	point = &(map->mgrid[y][x]);
	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z * map->zscale;
	x_location(&(tmp.y), &(tmp.z), map->xrotate);
	y_location(&(tmp.x), &(tmp.z), map->yrotate);
	z_location(&(tmp.x), &(tmp.y), map->zrotate);
	projection->x = (int)(tmp.x * map->zoom - tmp.y * map->zoom) * cos(map->alpha) + map->x_offset;
	projection->y = (int)(-tmp.z * map->zoom + (tmp.x * map->zoom + tmp.y * map->zoom) 
		* sin(map->beta) + map->y_offset);
	if (map->use_color)
		projection->rgba = point->color;
	else
		projection->rgba = point->mapcolor;
}

void	draw_line(t_fdf *fdf, int x, int y)
{
    if (x == 0 && y == 0)
        projection(fdf->map, y, x);
    if (y + 1 < fdf->map->rows)
    {
        projection(fdf->map, y + 1, x);
        two_points_draw_line(fdf, fdf->map->grid[y][x], fdf->map->grid[y + 1][x]);
    }
    if (x + 1 < fdf->map->cols)
    {
        projection(fdf->map, y, x + 1);
        two_points_draw_line(fdf, fdf->map->grid[y][x], fdf->map->grid[y][x + 1]);
    }
}
