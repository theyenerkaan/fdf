/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:04 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/06 22:21:27 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	alloc_grid(t_map *map)
{
    int i;

    i = -1;
    map->mgrid = (t_mpoint **)malloc(sizeof(t_mpoint *) * map->rows);
    map->grid = (t_point **)malloc(sizeof(t_point *) * map->rows);
    if (!(map->mgrid) || !(map->grid))
    {
        free_map(map);
        error_exit("Failed to allocate memory for map grid");
    }
    while (++i < map->rows)
    {
        map->mgrid[i] = (t_mpoint *)malloc(sizeof(t_mpoint) * map->cols);
        map->grid[i] = (t_point *)malloc(sizeof(t_point) * map->cols);
        if (!(map->mgrid[i]) || !(map->grid[i]))
        {
            if (i + 1 < map->rows)
            {
                map->mgrid[i + 1] = NULL;
                map->grid[i + 1] = NULL;
            }
            free_map(map);
            error_exit("Failed to allocate memory for map grid");
        }
    }
}

void	filling_map(t_map *map)
{
	map->rows = 0;
	map->cols = 0;
	map->high = INTMAX_MAX;
	map->deep = INTMAX_MIN;
	map->use_color = false;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->zoom = 1;
	map->zscale = 1;
	map->mgrid = NULL;
	map->grid = NULL;
}

static t_map	*parse_map(char *mapname)
{
	int fd;
	t_map *map;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		close(fd);
		error_exit("Failed to allocate memory for map");
	}
	filling_map(map);
	set_size(fd, map);
	close(fd);
	alloc_grid(map);
	map->interval = ft_max(2, ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2);
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		error_map(fd, map, "Failed to open map file");
	set_map(fd, map);
	close(fd);
	// renkleri ayarlamak için fonk yaz buraya
	return (map);
	
}

static t_fdf	*init_prog(char *mapname)
{
	static t_fdf	fdf;

	fdf.map = parse_map(mapname);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2 || !valid_map(av[1]))
		error_exit("Usage: ./fdf <map.fdf>");
	fdf = init_prog(av[1]);
	
}