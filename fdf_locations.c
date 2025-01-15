/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_locations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:08:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/15 06:34:06 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_location(double *y, double *z, double alpha)
{
	double	appearance_y;
	
	appearance_y = *y;
	*y = appearance_y * cos(alpha) + *z * sin(alpha);
	*z = -appearance_y * sin(alpha) + *z * cos(alpha);
}
void	y_location(double *x, double *z, double beta)
{
	double	appearance_x;
	
	appearance_x = *x;
	*x = appearance_x * cos(beta) + *z * sin(beta);
	*z = -appearance_x * sin(beta) + *z * cos(beta);
}

void	z_location(double *x, double *y, double gamma)
{
	double	appearance_x;
	
	appearance_x = *x;
	*x = appearance_x * cos(gamma) - *y * sin(gamma);
	*y = appearance_x * sin(gamma) + *y * cos(gamma);
}

int	choise_color(t_point instant, t_point a, t_point b)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (abs(b.x - a.x) > abs(b.y - a.y))
		percentage = (double)(instant.x - a.x) / (b.x - a.x);
	else
		percentage = (double)(instant.y - a.y) / (b.y - a.y);
	red = (int)((1 - percentage) * ((a.rgba >> 24) & 0xFF) + percentage * ((b.rgba >> 24) & 0xFF));
	green = (int)((1 - percentage) * ((a.rgba >> 16) & 0xFF) + percentage * ((b.rgba >> 16) & 0xFF));
	blue = (int)((1 - percentage) * ((a.rgba >> 8) & 0xFF) + percentage * ((b.rgba >> 8) & 0xFF));
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}


void two_points_draw_line(t_fdf *fdf, t_point a, t_point b)
{
    int     point[2];
    t_point instant;

    instant.x = a.x;
    instant.y = a.y;
    point[0] = abs(b.x - a.x) - abs(b.y - a.y);
    while ( (int)instant.x != (int)b.x || (int)instant.y != (int)b.y )
    {
        if ((uint32_t)instant.x < WIDTH && (uint32_t)instant.y < HEIGHT)
            mlx_pixel_put(fdf->mlx, fdf->win, (int)instant.x, (int)instant.y, choise_color(instant, a, b));
        point[1] = 2 * point[0];
        if (point[1] > -abs(b.y - a.y))
        {
            point[0] -= abs(b.y - a.y);
            instant.x += (a.x < b.x) ? 1 : -1;
        }
        if (point[1] < abs(b.x - a.x))
        {
            point[0] += abs(b.x - a.x);
            instant.y += (a.y < b.y) ? 1 : -1;
        }
    }
}
