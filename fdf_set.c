/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:23:11 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/08 08:09:35 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_point(t_mpoint *point, char *value, int i, int j,
					t_map *map, int x_offset, int y_offset)
{
	double	z_value;

	z_value = (double)ft_atoi(value) * map->interval;
	point->x = (double)j * map->interval - x_offset;
	point->y = (double)i * map->interval - y_offset;
	point->z = z_value;
	point->mapcolor = parse_color(0, map, value);

	map->high = ft_max(map->high, z_value);
	map->deep = ft_min(map->deep, z_value);
}

void	set_columns(int fd, t_map *map, char **split, int i)
{
	int			j;
	int			x_offset;
	int			y_offset;

	x_offset = (map->cols - 1) * map->interval / 2;
	y_offset = (map->rows - 1) * map->interval / 2;
	j = 0;
	while (split[j])
	{
		if (!ft_isdigit(*split[j]) && *split[j] != '-')
			error_map(fd, map, "Invalid map");
		set_point(&(map->mgrid[i][j]), split[j], i, j, map, x_offset, y_offset);
		j++;
	}
	if (i == 0)
		map->cols = j;
	else if (map->cols != j)
		error_map(fd, map, "Invalid map");
}


void	set_map(int fd, t_map *map)
{
	char *line;
	char *tmp;
	char **split;
	int i;

	i = 0;
	while(i < map->rows)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			error_map(fd, map, "Failed to read map file");
		line = ft_strtrim(tmp, "\n");
		if (!line)
			error_map(fd, map, "Failed to allocate memory for line");
		split = ft_split(line, ' ');
		if (!split)
			error_map(fd, map, "Failed to allocate memory for line");
		set_columns(fd, map, split, i);
		free(tmp);
		free(line);
		ft_free_split((void **)split, map->cols);
	}
	
}

static int	get_line(int fd, t_map *map, char line)
{
	char *tmp;
	char **split;
	int i;

	i = 0;
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
		i++;
	}
	ft_free_split((void **)split, i);
	return (free(line), free(tmp), i);
}

void	set_size(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		error_map(fd, map, "Failed to read map file");
	map->cols = get_line(fd, line, ' ');
	if(map->cols == 0)
		error_map(fd, map, "Invalid map");
	map->rows = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->rows++;
		if (map->cols != get_line(fd, map, line))
			error_map(fd, map, "Invalid map");
	}
}

