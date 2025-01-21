/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 05:26:27 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/22 00:42:16 by yenyilma         ###   ########.fr       */
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

int	get_palette_color(double perc)
{
	if (perc < 0.1)
		return (COLOR_1);
	else if (perc < 0.2)
		return (COLOR_2);
	else if (perc < 0.3)
		return (COLOR_3);
	else if (perc < 0.4)
		return (COLOR_4);
	else if (perc < 0.5)
		return (COLOR_5);
	else if (perc < 0.6)
		return (COLOR_6);
	else if (perc < 0.7)
		return (COLOR_7);
	else if (perc < 0.8)
		return (COLOR_8);
	else if (perc < 0.9)
		return (COLOR_9);
	else if (perc < 1.0)
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

void	set_color(t_map *map)
{
	int		i;
	int 	j;
	double	pers;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			pers = percent(map->deep, map->high, map->mgrid[i][j].z);
			if (map->high == map->deep)
			{
				pers = 0.5;
			}
			else if (pers < 0.0)
				pers = 0.0;
			else if (pers > 1.0)
				pers = 1.0;
			else
				map->mgrid[i][j].color = get_palette_color(pers);
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
