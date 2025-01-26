/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 11:22:12 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_menu_background(t_fdf *fdf, t_menu_params *params,
	int height, int bg_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < params->width)
		{
			my_mlx_pixel_put(fdf, params->x + j, params->y + i, bg_color);
			j++;
		}
		i++;
	}
}

void	draw_centered_bold_text(t_fdf *fdf, t_menu_params *params, char *text)
{
	int	centered_x;

	centered_x = params->x + ((params->width - (ft_strlen(text) * 10)) / 2);
	mlx_string_put(fdf->mlx, fdf->win, centered_x,
		params->y, params->color, text);
	mlx_string_put(fdf->mlx, fdf->win, centered_x + 1,
		params->y, params->color, text);
	mlx_string_put(fdf->mlx, fdf->win, centered_x,
		params->y + 1, params->color, text);
	mlx_string_put(fdf->mlx, fdf->win, centered_x + 1,
		params->y + 1, params->color, text);
	params->y += 30;
}

static void	set_menu_controls(t_fdf *fdf, t_menu_params *params)
{
	draw_centered_bold_text(fdf, params, "=== Controls ===");
	draw_centered_bold_text(fdf, params, "Move: Arrow Keys");
	draw_centered_bold_text(fdf, params, "Zoom: +/-");
	draw_centered_bold_text(fdf, params, "Rotate: A/D/W/S");
	draw_centered_bold_text(fdf, params, "Scale Z: T/G");
	draw_centered_bold_text(fdf, params, "Toggle Color: C");
	draw_centered_bold_text(fdf, params, "Reset View: 0");
}

static void	set_menu_projection(t_fdf *fdf, t_menu_params *params)
{
	draw_centered_bold_text(fdf, params, "Projection:");
	draw_centered_bold_text(fdf, params, "1 - Isometric (~30°)");
	draw_centered_bold_text(fdf, params, "2 - Dimetric (~37°)");
	draw_centered_bold_text(fdf, params, "3 - Custom");
	draw_centered_bold_text(fdf, params, "4 - 45 Degree");
	draw_centered_bold_text(fdf, params, "5 - 20 Degree");
	draw_centered_bold_text(fdf, params, "Quit: Q or ESC");
	draw_centered_bold_text(fdf, params, "Start: Any of the Zoom Keys");
}

int	set_menu(t_fdf *fdf)
{
	t_menu_params	params;
	int				bg_height;

	params.x = 10;
	params.y = 20;
	params.width = 320;
	params.color = 0x07B21B;
	bg_height = 400;
	if (!fdf || !fdf->mlx || !fdf->win)
	{
		ft_printf("Error: MiniLibX not initialized.\n");
		return (0);
	}
	draw_menu_background(fdf, &params, bg_height, 0x101010);
	set_menu_controls(fdf, &params);
	set_menu_projection(fdf, &params);
	draw_centered_bold_text(fdf, &params, "!!! Have Fun !!!");
	return (0);
}
