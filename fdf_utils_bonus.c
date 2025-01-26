/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 16:49:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	radiant(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

int	choise_color(t_point instant, t_point a, t_point b)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (a.rgba == b.rgba)
		return (a.rgba);
	if (abs(b.x - a.x) > abs(b.y - a.y))
		percentage = percent(a.x, b.x, instant.x);
	else
		percentage = percent(a.y, b.y, instant.y);
	red = radiant((a.rgba >> 16) & 0xFF, (b.rgba >> 16) & 0xFF, percentage);
	green = radiant((a.rgba >> 8) & 0xFF, (b.rgba >> 8) & 0xFF, percentage);
	blue = radiant((a.rgba) & 0xFF, (b.rgba) & 0xFF, percentage);
	return ((0xFF << 24) | (red << 16) | (green << 8) | blue);
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = fdf->addr + (y * fdf->line_len + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}
