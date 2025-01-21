/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:50 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/22 00:32:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include <X11/keysym.h>
# include "mlx/mlx.h"
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH			1920
# define HEIGHT			1080

# define KEY_MAX		65535

#define BACKGROUND		0x808080
#define COLOR_1			0x2841BF
#define COLOR_2			0x2B40BA
#define COLOR_3			0x2E40B4
#define COLOR_4			0x313FAF
#define COLOR_5			0x353FAA
#define COLOR_6			0xf2f2f2
#define COLOR_7			0x3B3EA0
#define COLOR_8			0x3E3E9A
#define COLOR_9			0x423D95
#define COLOR_10		0x453D90
#define COLOR_11		0xf2f2f2

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
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	t_map	*map;
	int		bpp;
	int		line_len;
	int		endian;
	int		keys[KEY_MAX + 1];
}	t_fdf;


int		choise_color(t_point instant, t_point a, t_point b);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
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
void	set_menu(void *mlx, void *win);
int		map_view(void *view);
int		rotate_view(void *view);
void	default_view(t_map *map);
void	image_view(void *view);
double	percent(int start, int end, int current);
int	radiant(int start, int end, double percentage);
void	draw_background(t_fdf *base, int color);
void	projection(t_map *map, int i, int j);
void	draw_line(t_fdf *fdf, int x, int y);
void	x_location(double *y, double *z, double alpha);
void	y_location(double *x, double *z, double beta);
void	z_location(double *x, double *y, double gamma);
void	two_points_draw_line(t_fdf *view, t_point a, t_point b);
int		kaan(void *view);
int		key_press(int keycode, void *win);
int		key_release(int keycode, void *win);
void	clear_keys(int *keys, int index);
int		interpolate_color(int start, int end, double t);
int		get_palette_color(double pers);

#endif
 