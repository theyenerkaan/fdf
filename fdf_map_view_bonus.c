/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_view_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:00:40 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/30 14:39:28 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	default_view(t_map *map)
{
	map->use_color = false;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->x_rotate = 0;
	map->y_rotate = 0;
	map->z_rotate = 0;
	map->zoom = 1;
	map->zscale = 1;
}

static void	handle_movement_and_zoom(t_fdf *fdf)
{
	if (fdf->keys[XK_Left])
		fdf->map->x_offset -= 5;
	if (fdf->keys[XK_Right])
		fdf->map->x_offset += 5;
	if (fdf->keys[XK_Up])
		fdf->map->y_offset -= 5;
	if (fdf->keys[XK_Down])
		fdf->map->y_offset += 5;
	if (fdf->keys[XK_asterisk])
		fdf->map->zoom -= 0.02;
	if (fdf->keys[XK_minus])
		fdf->map->zoom += 0.02;
	if (fdf->keys[XK_2])
	{
		fdf->map->alpha = 0.6370452;
		fdf->map->beta = 0.6370452;
	}
}

static void	handle_rotation_and_scale(t_fdf *fdf)
{
	if (fdf->keys[XK_t])
		fdf->map->zscale += 0.03;
	if (fdf->keys[XK_g])
		fdf->map->zscale -= 0.03;
	if (fdf->keys[XK_s])
		fdf->map->x_rotate += 0.02;
	if (fdf->keys[XK_d])
		fdf->map->y_rotate += 0.02;
	if (fdf->keys[XK_a])
		fdf->map->z_rotate += 0.02;
	if (fdf->keys[XK_w])
		fdf->map->zoom -= 0.02;
	if (fdf->keys[XK_e])
		fdf->map->zoom += 0.02;
	if (fdf->keys[XK_r])
		fdf->map->z_rotate -= 0.02;
	if (fdf->keys[XK_c])
		fdf->map->use_color = !(fdf->map->use_color);
	if (fdf->keys[XK_1])
	{
		fdf->map->alpha = 0.523599;
		fdf->map->beta = 0.523599;
	}
}

int	map_view(void *view)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	if (fdf->keys[XK_0])
		default_view(fdf->map);
	if (fdf->keys[XK_Escape] || fdf->keys[XK_q])
		mlx_loop_end(fdf->mlx);
	handle_movement_and_zoom(fdf);
	handle_rotation_and_scale(fdf);
	return (0);
}

int	rotate_view(void *view)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	if (fdf->keys[XK_3])
	{
		fdf->map->alpha = 0.46373398 / 2;
		fdf->map->beta = 0.46373398;
	}
	if (fdf->keys[XK_4])
	{
		fdf->map->alpha = 0.785398;
		fdf->map->beta = 1.047198;
	}
	if (fdf->keys[XK_5])
	{
		fdf->map->alpha = 0.349066;
		fdf->map->beta = 1.221730;
	}
	return (0);
}
