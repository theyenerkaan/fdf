/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:23:11 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/06 22:14:11 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		// colunm fonk yazdır
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
		if (map->cols != get_line(fd, map, line))
			error_map(fd, map, "Invalid map");
		map->rows++;
	}
}