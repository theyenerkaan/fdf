/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 12:26:52 by yenyilma         ###   ########.fr       */
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

void	draw_centered_bold_text(t_fdf *fdf, t_menu_params *params,
	char *text, int color)
{
	int	centered_x;

	centered_x = params->x + params->padding +
		((params->width - params->padding - (ft_strlen(text) * 10)) / 2);
	mlx_string_put(fdf->mlx, fdf->win, centered_x, params->y, color, text);
	mlx_string_put(fdf->mlx, fdf->win, centered_x + 1, params->y, color, text);
	mlx_string_put(fdf->mlx, fdf->win, centered_x, params->y + 1, color, text);
	mlx_string_put(fdf->mlx, fdf->win, centered_x + 1, params->y + 1, color, text);
	params->y += params->spacing;
}

static void	set_menu_controls(t_fdf *fdf, t_menu_params *params)
{
	params->spacing = 37;
	params->padding = 10;
	draw_centered_bold_text(fdf, params, "=== Controls ===", 0xFFFFFF); // Beyaz renk
	params->spacing = 25;
	draw_centered_bold_text(fdf, params, "Move: Arrow Keys", params->color);
	draw_centered_bold_text(fdf, params, "Zoom: +/-", params->color);
	draw_centered_bold_text(fdf, params, "Rotate: A/D/W/S", params->color);
	draw_centered_bold_text(fdf, params, "Scale Z: T/G", params->color);
	draw_centered_bold_text(fdf, params, "Toggle Color: C", params->color);
	draw_centered_bold_text(fdf, params, "Reset View: 0", params->color);
}

static void	set_menu_projection(t_fdf *fdf, t_menu_params *params)
{
	params->spacing = 37;
	draw_centered_bold_text(fdf, params, "Projection:", 0xFFFFFF); // Beyaz renk
	params->spacing = 25;
	draw_centered_bold_text(fdf, params, "1 - Isometric ( ~30° )", params->color);
	draw_centered_bold_text(fdf, params, "2 - Dimetric ( ~37° )", params->color);
	draw_centered_bold_text(fdf, params, "3 - Custom", params->color);
	draw_centered_bold_text(fdf, params, "4 - 45 Degree", params->color);
	params->spacing = 37;
	draw_centered_bold_text(fdf, params, "5 - 20 Degree", params->color);
	params->spacing = 25;
	draw_centered_bold_text(fdf, params, "Quit: Q or ESC", params->color);
	params->spacing = 57;
	draw_centered_bold_text(fdf, params, "Start: Any of the Zoom Keys", params->color);
}

int	set_menu(t_fdf *fdf)
{
	t_menu_params	params;
	int				bg_height;

	params.x = 11;
	params.y = 11;
	params.width = 333;
	params.color = 0x07B21B;
	bg_height = 457;

	if (!fdf || !fdf->mlx || !fdf->win)
	{
		ft_printf("Error: MiniLibX not initialized.\n");
		return (0);
	}
	draw_menu_background(fdf, &params, bg_height, 0x101010);
	set_menu_controls(fdf, &params);
	set_menu_projection(fdf, &params);
	params.spacing = 29;
	params.padding = 10;
	draw_centered_bold_text(fdf, &params, "!!! Have Fun !!!", 0xFFD700);
	draw_centered_bold_text(fdf, &params, "=== created by Y   K   Y ===", 0x4b0082);
	return (0);
}
