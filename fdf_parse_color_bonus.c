/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:23:11 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 16:48:47 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	make_upper(unsigned int i, char *c)
{
	i++;
	*c = ft_toupper(*c);
}

int	parse_color(int fd, t_map *map, char *split)
{
	while (*split == '-')
		split++;
	while (ft_isdigit(*split))
		split++;
	if (*split == ',')
		split++;
	else
		return (0x808080);
	if ((ft_strncmp(split, "0X", 2) && ft_strncmp(split, "0x", 2)))
		error_map(fd, map, "Invalid color format");
	split += 2;
	ft_striteri(split, &make_upper);
	return ((ft_atoi_base(split, "0123456789ABCDEF")) | 0xFF << 24);
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
