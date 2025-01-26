/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:50 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 14:31:17 by yenyilma         ###   ########.fr       */
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

#define BACKGROUND		0x00000000
#define COLOR_1			0xFF8A2BE2  // Mavi-Mor (BlueViolet)
#define COLOR_2			0xFF9400D3  // Koyu Mor (DarkViolet)
#define COLOR_3			0xFF8B00FF  // Neon Mor
#define COLOR_4			0xFF6A0DAD  // Derin Mor (Purple)
#define COLOR_5			0xFFD700FF  // Neon Pembe (Deep Pink)
#define COLOR_6			0xFFFF1493  // Neon Pembe (Deep Pink)
#define COLOR_7			0xFFFF69B4  // Açık Pembe (Hot Pink)
#define COLOR_8			0xFFC71585  // Orta Pembe (Medium Violet Red)
#define COLOR_9			0xFF7B68EE  // Açık Mor (Medium Slate Blue)
#define COLOR_10		0xFF4169E1  // Koyu Mavi (Royal Blue)
#define COLOR_11		0xFF00FFFF  // Neon Mavi (Cyan)



typedef	enum s_bool
{
	false,
	true
}								t_bool;

typedef struct g_mlx_image
{
	uint32_t	width;
	uint32_t	height;
}								t_mlx_image;

typedef struct s_mpoint
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		color;
}								t_mpoint;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		rgba;
}								t_point;

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
	double			x_rotate;
	double			y_rotate;
	double			z_rotate;
	double			zoom;
	double			zscale;
	int				mhigh;
	int				mdeep;
	t_mpoint		**mgrid;
	t_point			**grid;
}								t_map;

typedef struct s_menu_params
{
	int x;
	int y;
	int width;
	int color;
	int spacing;
	int padding;
}								t_menu_params;


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
}								t_fdf;



void	alloc_grid(t_map *map);
void	free_map(t_map *map);
void	ft_free_split(void **split, size_t len);
t_map	*parse_map(char *mapname);
int		ft_atoi_base(const char *nptr, const char *base);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		valid_map(const char *mapname);
void	error_map(int fd, t_map *map, const char *msg);
void	error_exit(const char *msg);
int		get_line(int fd, t_map *map, char *line);
void	set_columns(int fd, t_map *map, char **split, int i);
double	percent(int start, int end, int current);
int		get_palette_color(double perc);
void	clear_keys(int *keys, int size);
int		key_release(int keycode, void *param);
int		key_press(int keycode, void *param);
void	image_view(void *view);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
int		choise_color(t_point instant, t_point a, t_point b);
int		loop_full(void *view);
int		map_view(void *view);
int		rotate_view(void *view);
int		set_menu(t_fdf *fdf);
int		parse_color(int fd, t_map *map, char *value);
void	x_location(double *y, double *z, double alpha);
void	y_location(double *x, double *z, double beta);
void	z_location(double *x, double *y, double gamma);








// int		choise_color(t_point instant, t_point a, t_point b);
// void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
// int		valid_map(const char *mapname);
// void	error_exit(const char *msg);
// void	set_size(int fd, t_map *map);
// void	error_map(int fd, t_map *map, const char *msg);
// int		ft_max(int a, int b);
// int		ft_min(int a, int b);
// void	ft_free_split(void **split, size_t len);
// void	free_map(t_map *map);
// void	set_map(int fd, t_map *map);
// void	set_color(t_map *map);
// void	set_point(t_mpoint *point, char *value, int i, int j,
// 					t_map *map, int x_offset, int y_offset);
// void	set_columns(int fd, t_map *map, char **split, int i);
// int		ft_atoi_base(const char *nptr, const char *base);
// int		rotate_view(void *view);
// void	default_view(t_map *map);
// void	image_view(void *view);
// double	percent(int start, int end, int current);
// int		radiant(int start, int end, double percentage);
// void	draw_background(t_fdf *base, int color);
// void	projection(t_map *map, int i, int j);
// void	draw_line(t_fdf *fdf, int x, int y);
// void	two_points_draw_line(t_fdf *view, t_point a, t_point b);
// int		kaan(void *view);
// int		key_press(int keycode, void *win);
// int		key_release(int keycode, void *win);
// void	clear_keys(int *keys, int index);
// int		interpolate_color(int start, int end, double t);
// int		get_palette_color(double pers);

#endif
 