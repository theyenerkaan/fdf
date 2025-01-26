/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:50 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 15:08:09 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include "X11/keysym.h"
# include "mlx/mlx.h"
# include "stdint.h"
# include "limits.h"
# include "fcntl.h"
# include "math.h"

# define WIDTH			1920
# define HEIGHT			1080

# define KEY_MAX		65535

# define BACKGROUND		0x00000000
# define COLOR_1		0xFF8A2BE2
# define COLOR_2		0xFF9400D3
# define COLOR_3		0xFF8B00FF
# define COLOR_4		0xFF6A0DAD
# define COLOR_5		0xFFD700FF
# define COLOR_6		0xFFFF1493
# define COLOR_7		0xFFFF69B4
# define COLOR_8		0xFFC71585
# define COLOR_9		0xFF7B68EE
# define COLOR_10		0xFF4169E1
# define COLOR_11		0xFF00FFFF

typedef enum s_bool
{
	false,
	true
}								t_bool;

typedef struct g_mlx_image
{
	uint32_t		width;
	uint32_t		height;
}								t_mlx_image;

typedef struct s_mpoint
{
	double			x;
	double			y;
	double			z;
	int				mapcolor;
	int				color;
}								t_mpoint;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				rgba;
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
	int				x;
	int				y;
	int				width;
	int				color;
	int				spacing;
	int				padding;
}								t_menu_params;

typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	t_map			*map;
	int				bpp;
	int				line_len;
	int				endian;
	int				keys[KEY_MAX + 1];
}								t_fdf;

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void	set_columns(int fd, t_map *map, char **split, int i);
int		choise_color(t_point instant, t_point a, t_point b);
int		ft_atoi_base(const char *nptr, const char *base);
void	error_map(int fd, t_map *map, const char *msg);
void	x_location(double *y, double *z, double alpha);
void	z_location(double *x, double *y, double gamma);
void	y_location(double *x, double *z, double beta);
int		parse_color(int fd, t_map *map, char *value);
int		get_line(int fd, t_map *map, char *line);
double	percent(int start, int end, int current);
void	ft_free_split(void **split, size_t len);
int		key_release(int keycode, void *param);
int		key_press(int keycode, void *param);
void	clear_keys(int *keys, int size);
int		get_palette_color(double perc);
int		valid_map(const char *mapname);
void	error_exit(const char *msg);
t_map	*parse_map(char *mapname);
int		rotate_view(void *view);
void	image_view(void *view);
void	alloc_grid(t_map *map);
int		loop_full(void *view);
void	free_map(t_map *map);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		map_view(void *view);
int		set_menu(t_fdf *fdf);

#endif
