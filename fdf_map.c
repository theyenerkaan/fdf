/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:00:40 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/21 22:58:57 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	default_view(t_map *map)
{
	map->use_color = false;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->zoom = 1;
	map->zscale = 1;
}

int	map_view(void *view)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	if (fdf->keys[XK_0])
		default_view(fdf->map);
	if (fdf->keys[XK_Escape] || fdf->keys[XK_q])
		mlx_loop_end(fdf->mlx);
	if (fdf->keys[XK_Left])
		fdf->map->x_offset -= 5;
	if (fdf->keys[XK_Right])
		fdf->map->x_offset += 5;
	if (fdf->keys[XK_Up])
		fdf->map->y_offset -= 5;
	if (fdf->keys[XK_Down])
		fdf->map->y_offset += 5;
	if (fdf->keys[XK_equal]) // '='
		fdf->map->zoom -= 0.02;
	if (fdf->keys[XK_minus]) // '-'
		fdf->map->zoom += 0.02;
	if (fdf->keys[XK_t])
		fdf->map->zscale += 0.03;
	if (fdf->keys[XK_g])
		fdf->map->zscale -= 0.03;
	if (fdf->keys[XK_slash]) // '/'
		fdf->map->zscale = 0.03;
	if (fdf->keys[XK_s])
		fdf->map->xrotate += 0.02;
	if (fdf->keys[XK_d])
		fdf->map->yrotate += 0.02;
	if (fdf->keys[XK_a])
		fdf->map->zrotate += 0.02;
	if (fdf->keys[XK_w])
		fdf->map->zoom -= 0.02;
	if (fdf->keys[XK_e])
		fdf->map->zoom += 0.02;
	if (fdf->keys[XK_r])
		fdf->map->zrotate -= 0.02;
	return (0);
}

int	rotate_view(void *view)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	if (fdf->keys[XK_c])
		fdf->map->use_color = !(fdf->map->use_color);
	if (fdf->keys[XK_1])
	{
		fdf->map->alpha = 0.523599; // ~30°
		fdf->map->beta = fdf->map->alpha;
	}
	if (fdf->keys[XK_2])
	{
		fdf->map->alpha = 0.6370452;
		fdf->map->beta = fdf->map->alpha;
	}
	if (fdf->keys[XK_3])
	{
		fdf->map->alpha = 0.46373398 / 2;
		fdf->map->beta = 0.46373398;
	}
	if (fdf->keys[XK_4])
	{
		fdf->map->alpha = 0.785398; // 45°
		fdf->map->beta = 1.047198;  // 60°
	}
	if (fdf->keys[XK_5])
	{
		fdf->map->alpha = 0.349066; // ~20°
		fdf->map->beta = 1.221730;  // ~70°
	}
	return (0);
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