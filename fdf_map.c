/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:00:40 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/16 19:46:30 by yenyilma         ###   ########.fr       */
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
	if (fdf->keys[MLX_KEY_0])
		default_view(fdf->map);
	if (fdf->keys[MLX_KEY_ESCAPE])
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->keys[MLX_KEY_Q])
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->keys[MLX_KEY_LEFT])
		fdf->map->x_offset -= 5;
	if (fdf->keys[MLX_KEY_RIGHT])
		fdf->map->x_offset += 5;
	if (fdf->keys[MLX_KEY_DOWN])
		fdf->map->y_offset += 5;
	if (fdf->keys[MLX_KEY_UP])
		fdf->map->y_offset -= 5;
	if (fdf->keys[MLX_KEY_EQUAL])
		fdf->map->zoom -= 0.02;
	if (fdf->keys[MLX_KEY_MINUS])
		fdf->map->zoom += 0.02;
	if (fdf->keys[MLX_KEY_T])
		fdf->map->zscale += 1;
	if (fdf->keys[MLX_KEY_G])
		fdf->map->zscale -= 0.03;
	if (fdf->keys[MLX_KEY_SLASH])
		fdf->map->zscale = 1;
	if (fdf->keys[MLX_KEY_S])
		fdf->map->xrotate += 0.02;
	if(fdf->keys[MLX_KEY_D])
		fdf->map->yrotate += 0.02;
	if(fdf->keys[MLX_KEY_A])
		fdf->map->zrotate += 0.02;
	if(fdf->keys[MLX_KEY_W])
		fdf->map->zoom -= 0.02;
	if(fdf->keys[MLX_KEY_E])
		fdf->map->zoom += 0.02;
	if(fdf->keys[MLX_KEY_R])
		fdf->map->zrotate -= 0.02;
	return (0);
}

int	rotate_view(void *view)
{
	t_fdf *fdf;

	fdf = (t_fdf *)view;
	if (fdf->keys[MLX_KEY_C])
		fdf->map->use_color = !(fdf->map->use_color);
	if (fdf->keys[MLX_KEY_1])
	{
		fdf->map->alpha = 0.523599;
		fdf->map->beta = fdf->map->alpha;
	}
	if (fdf->keys[MLX_KEY_2])
	{
		fdf->map->alpha = 0.6370452;
		fdf->map->beta = fdf->map->alpha;
	}
	if (fdf->keys[MLX_KEY_3])
	{
		fdf->map->alpha = 0.46373398 / 2;
		fdf->map->beta = 0.46373398;
	}
	if (fdf->keys[MLX_KEY_4])
	{
		fdf->map->alpha = 0.785398; // 45°
		fdf->map->beta = 1.047198;	// 60°
	}
	if (fdf->keys[MLX_KEY_5])
	{
		fdf->map->alpha = 0.349066; // 20°
		fdf->map->beta = 1.221730;	// 70°
	}
	return (0);
}

int	image_view(void *view)
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
			// draw_line(fdf, j, i); // seg yediğimiz yer
			j++;
		}
		i++;
	}
	return (0);
}