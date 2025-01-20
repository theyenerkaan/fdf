/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 05:26:27 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/20 15:27:13 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 06:30:00 by yourname          #+#    #+#             */
/*   Updated: 2025/01/08 06:30:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	get_color_by_index(int index)
{
	if (index == 0)
		return (COLOR_1);
	if (index == 1)
		return (COLOR_2);
	if (index == 2)
		return (COLOR_3);
	if (index == 3)
		return (COLOR_4);
	if (index == 4)
		return (COLOR_5);
	if (index == 5)
		return (COLOR_6);
	if (index == 6)
		return (COLOR_7);
	if (index == 7)
		return (COLOR_8);
	if (index == 8)
		return (COLOR_9);
	if (index == 9)
		return (COLOR_10);
	return (COLOR_11);
}

int	interpolate_color(int start, int end, double t)
{
	int	sr;
	int	sg;
	int	sb;
	int	er;
	int	eg;
	int	eb;
	int	r;
	int	g;
	int	b;

	sr = (start >> 16) & 0xFF;
	sg = (start >> 8) & 0xFF;
	sb = start & 0xFF;
	er = (end >> 16) & 0xFF;
	eg = (end >> 8) & 0xFF;
	eb = end & 0xFF;
	r = (int)((1 - t) * sr + t * er);
	g = (int)((1 - t) * sg + t * eg);
	b = (int)((1 - t) * sb + t * eb);
	return ((r << 16) | (g << 8) | b);
}
#include <stdio.h>
int	get_palette_color(double pers)
{
	int	color_start;
	int	color_end;
	int	index;
	double	fraction;

	if (pers < 0.0)
		pers = 0.0;
	else if (pers > 1.0)
		pers = 1.0;
	index = (int)(pers * 10.0);
	if (index >= 10)
		index = 10;
	color_start = get_color_by_index(index);
	color_end = get_color_by_index(index + 1);
	fraction = (pers * 10.0) - index;
	return (interpolate_color(color_start, color_end, fraction));
}
#include "stdio.h"
void	set_color(t_map *map)
{
	int		i;
	int 	j;
	float	pers;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			pers = (map->mgrid[i][j].z - map->deep) / (map->high - (map->deep));
			if (map->high == map->deep)
			{
				pers = 0.5;
			}
			if (pers < 0.0)
				pers = 0.0;
			if (pers > 1.0)
				pers = 1.0;
			map->mgrid[i][j].color = get_palette_color(pers);
			printf("elma pers %f\n", pers);

			j++;
		}
		i++;
	}
}
int	parse_color(int fd, t_map *map, char *value)
{
	double	z_value;
	double	percentage;
	int		color_start;
	int		color_end;

	z_value = (double)ft_atoi(value);
	percentage = (z_value - map->deep) / (map->high - map->deep);
	if (percentage < 0.0)
		percentage = 0.0;
	if (percentage > 1.0)
		percentage = 1.0;
	color_start = COLOR_1;
	color_end = COLOR_11;
	return (interpolate_color(color_start, color_end, percentage));
}
