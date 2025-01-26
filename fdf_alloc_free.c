/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_alloc_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:04 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 07:45:49 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_split(void **split, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->rows)
	{
		free(map->mgrid[i]);
		free(map->grid[i]);
		i++;
	}
	free(map->mgrid);
	free(map->grid);
	free(map);
}

void	alloc_grid(t_map *map)
{
	int	i;

	i = -1;
	map->mgrid = malloc(sizeof(t_mpoint *) * map->rows);
	map->grid = malloc(sizeof(t_point *) * map->rows);
	if (!(map->mgrid) || !(map->grid))
	{
		free_map(map);
		error_exit("Failed to allocate memory for map grid");
	}
	while (++i < map->rows)
	{
		map->mgrid[i] = malloc(sizeof(t_mpoint) * map->cols);
		map->grid[i] = malloc(sizeof(t_point) * map->cols);
		if (!(map->grid[i]) || !(map->mgrid[i]))
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
