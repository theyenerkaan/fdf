/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:50 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/06 22:20:33 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "mlx/include/MLX42/MLX42.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>

# define WIDTH				1919
# define HEIGHT				1010

typedef struct s_mpoint
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		color;
}				t_mpoint;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		rgba;
}			t_point;

typedef struct s_map
{
	int				rows;
	int				cols;
	int				high;
	int				deep;
	bool			use_color;
	double			x_offset;
	double			y_offset;
	double			interval;
	double			alpha;
	double			beta;
	double			xrotate;
	double			yrotate;
	double			zrotate;
	double			zoom;
	double			zscale;
	t_mpoint		**mgrid;
	t_point			**grid;
}					t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*img;
}				t_fdf;

int		valid_map(const char *mapname);
void	error_exit(const char *msg);
void	set_size(int fd, t_map *map);
void	error_map(int fd, t_map *map, const char *msg);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_free_split(void **split, size_t len);
void	set_map(int fd, t_map *map);
#endif
 