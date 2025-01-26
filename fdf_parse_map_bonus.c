/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:38:01 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 16:48:52 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	set_color(t_map *map)
{
	int		i;
	int		j;
	double	pers;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			pers = percent(map->deep, map->high, map->mgrid[i][j].z);
			if (map->high == map->deep)
				pers = 0.5;
			if (pers < 0.0)
				pers = 0.0;
			else if (pers > 1.0)
				pers = 1.0;
			map->mgrid[i][j].color = get_palette_color(pers);
			j++;
		}
		i++;
	}
}

static void	set_map(int fd, t_map *map)
{
	int		i;
	char	*line;
	char	*tmp;
	char	**split;

	i = 0;
	while (i < map->rows)
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
		i++;
	}
}

static void	set_size(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		error_map(fd, map, "Failed to read map file");
	map->cols = get_line(fd, map, line);
	if (map->cols == 0)
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

static void	filling_map(t_map *map)
{
	map->rows = 0;
	map->cols = 0;
	map->high = INT_MIN;
	map->deep = INT_MAX;
	map->use_color = false;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->x_rotate = 0;
	map->y_rotate = 0;
	map->z_rotate = 0;
	map->zoom = 0;
	map->zscale = 1;
	map->mgrid = NULL;
	map->grid = NULL;
}

t_map	*parse_map(char *mapname)
{
	int		fd;
	t_map	*map;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	map = malloc(sizeof(t_map));
	if (!map)
	{
		close(fd);
		error_exit("Failed to allocate memory for map");
	}
	filling_map(map);
	set_size(fd, map);
	close(fd);
	alloc_grid(map);
	map->interval = ft_max(2,
			ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2);
	fd = open(mapname, O_RDONLY, 0777);
	if (fd < 0)
		error_map(fd, map, "Failed to open map file");
	set_map(fd, map);
	close(fd);
	set_color(map);
	return (map);
}
