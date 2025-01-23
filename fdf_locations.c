/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_locations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:08:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/23 21:10:46 by yenyilma         ###   ########.fr       */
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

	if (a.rgba == b.rgba)
		return (a.rgba);
	if (abs(b.x - a.x) > abs(b.y - a.y))
		percentage = percent(a.x, b.x, instant.x);
	else
		percentage = percent(a.y, b.y, instant.y);
	red = radiant((a.rgba >> 24) & 0xFF, (b.rgba >> 24) & 0xFF, percentage);
	green = radiant((a.rgba >> 16) & 0xFF, (b.rgba >> 16) & 0xFF, percentage);
	blue = radiant((a.rgba >> 8) & 0xFF, (b.rgba >> 8) & 0xFF, percentage);
	return ((red << 24) | (green << 16) | blue << 8 | 0xFF);
}


// int	choise_color(t_point instant, t_point a, t_point b)
// {
// 	double	percentage;
// 	int		ar, ag, ab; // A noktasının R,G,B
// 	int		br, bg, bb; // B noktasının R,G,B
// 	int		r, g, bcol; // result R,G,B

// 	if (fabs((double)(b.x - a.x)) > fabs((double)(b.y - a.y)))
// 	{
// 		if (b.x == a.x)
// 			percentage = 1.0;
// 		else
// 			percentage = (instant.x - a.x) / (double)(b.x - a.x);
// 	}
// 	else
// 	{
// 		if (b.y == a.y)
// 			percentage = 1.0;
// 		else
// 			percentage = (instant.y - a.y) / (double)(b.y - a.y);
// 	}
// 	if (percentage < 0.0) percentage = 0.0;
// 	if (percentage > 1.0) percentage = 1.0;
// 	ar = (a.rgba >> 16) & 0xFF;
// 	ag = (a.rgba >> 8) & 0xFF;
// 	ab = (a.rgba) & 0xFF;
// 	br = (b.rgba >> 16) & 0xFF;
// 	bg = (b.rgba >> 8) & 0xFF;
// 	bb = (b.rgba) & 0xFF;
// 	r = (int)((1.0 - percentage) * ar + percentage * br);
// 	g = (int)((1.0 - percentage) * ag + percentage * bg);
// 	bcol = (int)((1.0 - percentage) * ab + percentage * bb);
// 	return ((r << 16) | (g << 8) | bcol);
// }


void two_points_draw_line(t_fdf *view, t_point a, t_point b)
{
    int     point[2];
    t_point instant;

    instant.x = a.x;
    instant.y = a.y;
    point[0] = abs(b.x - a.x) - abs(b.y - a.y);
    while ( (int)instant.x != (int)b.x || (int)instant.y != (int)b.y )
    {
        if ((uint32_t)instant.x < WIDTH && (uint32_t)instant.y < HEIGHT)
            my_mlx_pixel_put(view, (int)instant.x, (int)instant.y, choise_color(instant, a, b));
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
