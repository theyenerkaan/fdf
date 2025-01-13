/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:50 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/13 22:40:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH			1919
# define HEIGHT			1010

# define	MLX_KEY_SPACE			32
# define	MLX_KEY_APOSTROPHE		39
# define	MLX_KEY_COMMA			44
# define	MLX_KEY_MINUS			45
# define	MLX_KEY_PERIOD			46
# define	MLX_KEY_SLASH			47
# define	MLX_KEY_0				48
# define	MLX_KEY_1				49
# define	MLX_KEY_2				50
# define	MLX_KEY_3				51
# define	MLX_KEY_4				52
# define	MLX_KEY_5				53
# define	MLX_KEY_6				54
# define	MLX_KEY_7				55
# define	MLX_KEY_8				56
# define	MLX_KEY_9				57
# define	MLX_KEY_SEMICOLON		59
# define	MLX_KEY_EQUAL			61
# define	MLX_KEY_A				65
# define	MLX_KEY_C				67
# define	MLX_KEY_D				68
# define	MLX_KEY_E				69
# define	MLX_KEY_G				71
# define	MLX_KEY_Q				81
# define	MLX_KEY_R				82
# define	MLX_KEY_S				83
# define	MLX_KEY_T				84
# define	MLX_KEY_W				87
# define	MLX_KEY_LEFT			263
# define	MLX_KEY_RIGHT			262
# define	MLX_KEY_DOWN			264
# define	MLX_KEY_UP				265
# define	MLX_KEY_ESCAPE			256
# define	MLX_KEY_SLASH			47

#define BACKGROUND		0x000000
#define COLOR_1			0x2841BF
#define COLOR_2			0x2B40BA
#define COLOR_3			0x2E40B4
#define COLOR_4			0x313FAF
#define COLOR_5			0x353FAA
#define COLOR_6			0x383FA5
#define COLOR_7			0x3B3EA0
#define COLOR_8			0x3E3E9A
#define COLOR_9			0x423D95
#define COLOR_10		0x453D90
#define COLOR_11		0x483D8B

typedef	enum s_bool
{
	false,
	true
}				t_bool;

typedef struct g_mlx_image
{
	uint32_t	width;
	uint32_t	height;
}						t_mlx_image;

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
}				t_point;

typedef struct s_map
{
	int				rows;
	int				cols;
	int				high;
	int				deep;
	t_bool			use_color;
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
}						t_map;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_mlx_image	*img;
}				t_fdf;

int		valid_map(const char *mapname);
void	error_exit(const char *msg);
void	set_size(int fd, t_map *map);
void	error_map(int fd, t_map *map, const char *msg);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_free_split(void **split, size_t len);
void	free_map(t_map *map);
void	set_map(int fd, t_map *map);
void	set_color(t_map *map);
int		parse_color(int fd, t_map *map, char *value);
void	set_point(t_mpoint *point, char *value, int i, int j,
					t_map *map, int x_offset, int y_offset);
void	set_columns(int fd, t_map *map, char **split, int i);
void	set_menu(void *mlx);
void	map_view(void *view);
void	rotate_view(void *view);
void	zoom_view(int x, int y, void *view);
void	default_view(t_map *map);
void	image_view(void *view);
void	draw_background(t_map *img, int color);
void	projection(t_map *map, int i, int j);
void	draw_line(t_fdf *fdf, int x, int y);
void	x_location(double *y, double *z, double alpha);
void	y_location(double *x, double *z, double beta);
void	z_location(double *x, double *y, double gamma);
void	two_points_draw_line(t_mlx_image *view, t_point a, t_point b);


#endif
 