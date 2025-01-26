/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:23:11 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 16:48:21 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	get_line(int fd, t_map *map, char *line)
{
	char	*tmp;
	char	**split;
	int		i;

	i = 0;
	map->mhigh = 0;
	map->mdeep = 0;
	tmp = ft_strtrim(line, "\n");
	if (!tmp)
		error_map(fd, map, "Failed to allocate memory for line");
	split = ft_split(tmp, ' ');
	if (!split)
		error_map(fd, map, "Failed to allocate memory for line");
	while (split[i])
	{
		map->high = ft_max(map->high, ft_atoi(split[i]));
		map->deep = ft_min(map->deep, ft_atoi(split[i]));
		if (map->high > map->mhigh)
			map->mhigh = map->high;
		if (map->deep < map->mdeep)
			map->mdeep = map->deep;
		i++;
	}
	ft_free_split((void **)split, i);
	return (free(line), free(tmp), i);
}

void	set_columns(int fd, t_map *map, char **split, int i)
{
	t_mpoint	*point;
	int			x_offset;
	int			y_offset;
	int			j;

	j = -1;
	while (++j < map->cols)
	{
		if (!ft_isdigit(*split[j]) && *split[j] != '-')
			error_map(fd, map, "Invalid map");
		point = &(map->mgrid[i][j]);
		x_offset = (map->cols - 1) * map->interval / 2;
		y_offset = (map->rows - 1) * map->interval / 2;
		point->x = (double)j * (map->interval) - x_offset;
		point->y = (double)i * (map->interval) - y_offset;
		point->z = (double)ft_atoi(split[j]) * (map->interval);
		map->high = ft_max(map->high, point->z);
		map->deep = ft_min(map->deep, point->z);
		point->mapcolor = parse_color(fd, map, split[j]);
	}
}
