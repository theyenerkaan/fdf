/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_win_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:00:40 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 16:48:15 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	two_points_draw_line(t_fdf *view, t_point a, t_point b)
{
	int		point[2];
	t_point	instant;

	instant.x = a.x;
	instant.y = a.y;
	point[0] = abs(b.x - a.x) - abs(b.y - a.y);
	while ((int)instant.x != (int)b.x || (int)instant.y != (int)b.y)
	{
		if ((uint32_t)instant.x < WIDTH && (uint32_t)instant.y < HEIGHT)
			my_mlx_pixel_put(view, (int)instant.x, (int)instant.y,
				choise_color(instant, a, b));
		point[1] = 2 * point[0];
		if (point[1] > -abs(b.y - a.y))
		{
			point[0] -= abs(b.y - a.y);
			instant.x += (a.x < b.x);
			instant.x -= (b.x < a.x);
		}
		if (point[1] < abs(b.x - a.x))
		{
			point[0] += abs(b.x - a.x);
			instant.y += (a.y < b.y);
			instant.y -= (b.y < a.y);
		}
	}
}

static void	projection(t_map *map, int i, int j)
{
	t_mpoint	*point;
	t_mpoint	tmp;
	t_point		*projection;

	point = &(map->mgrid[i][j]);
	projection = &(map->grid[i][j]);
	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z * map->zscale;
	x_location(&(tmp.y), &(tmp.z), map->x_rotate);
	y_location(&(tmp.x), &(tmp.z), map->y_rotate);
	z_location(&(tmp.x), &(tmp.y), map->z_rotate);
	projection->x = (int)(tmp.x * map->zoom - tmp.y * map->zoom)
		* cos(map->alpha) + map->x_offset;
	projection->y = (int)(-tmp.z * map->zoom
			+ (tmp.x * map->zoom + tmp.y * map->zoom)
			* sin(map->beta) + map->y_offset);
	if (map->use_color)
		projection->rgba = point->color;
	else
		projection->rgba = point->mapcolor;
}

static void	draw_line(t_fdf *fdf, int x, int y)
{
	if (x == 0 && y == 0)
		projection(fdf->map, y, x);
	if (y + 1 < fdf->map->rows)
	{
		projection(fdf->map, y + 1, x);
		two_points_draw_line(fdf, fdf->map->grid[y][x],
			fdf->map->grid[y + 1][x]);
	}
	if (x + 1 < fdf->map->cols)
	{
		if (y == 0)
			projection(fdf->map, y, x + 1);
		two_points_draw_line(fdf, fdf->map->grid[y][x],
			fdf->map->grid[y][x + 1]);
	}
}

static void	draw_background(t_fdf *base, int color)
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

void	image_view(void *view)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	draw_background(fdf, BACKGROUND);
	i = 0;
	while (i < fdf->map->rows)
	{
		j = 0;
		while (j < fdf->map->cols)
		{
			draw_line(fdf, j, i);
			j++;
		}
		i++;
	}
}
