/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 04:57:00 by yenyilma         ###   ########.fr       */
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
	i = 0;
	while (i < map->rows)
	{
		free(map->mgrid[i]);
		free(map->grid[i]);
		i++;
	}
	free(map->mgrid);
	free(map->grid);
	free(map);
}

void	set_menu_controls(t_fdf *fdf, int x, int *y, int color)
{
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "=== Controls ===");
	*y += 35;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Move: Arrow Keys");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Zoom: +/-");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Rotate: A/D/W/S");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Scale Z: T/G");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Toggle Color: C");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Reset View: 0");
	*y += 20;
}

void	set_menu_projection(t_fdf *fdf, int x, int *y, int color)
{
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Projection:");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "  1 - Isometric (~30°)");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "  2 - Dimetric (~37°)");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "  3 - Custom");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "  4 - 45 Degree");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "  5 - 20 Degree");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Quit: Q or ESC");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, x, *y, color, "Start: Any of the Zoom Keys");
}


int	set_menu(t_fdf *fdf)
{
	int	x;
	int	y;
	int	color;

	x = 20;
	y = 20;
	color = 0xFFFFFF;
	if (!fdf || !fdf->mlx || !fdf->win)
	{
		ft_printf("Error: MiniLibX not initialized.\n");
		return (0);
	}
	set_menu_controls(fdf, x, &y, color);
	set_menu_projection(fdf, x, &y, color);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 30, color, "!!! Have Fun !!!");
	return (0);
}



int	kaan(void *view)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	map_view(fdf);
	rotate_view(fdf);
	image_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 1, 1);
	set_menu(fdf);
	return (0);
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = fdf->addr + (y * fdf->line_len + x * (fdf->bpp / 8));
	*(unsigned int *)dst = (0xFF << 24) | ((color >> 16) & 0xFF) |
            (color & 0x00FF00) | ((color & 0xFF) << 16);
}
