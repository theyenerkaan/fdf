/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:39:04 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 10:14:25 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_window(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free_map(fdf->map);
	free(fdf->mlx);
	exit(0);
	return (0);
}

static void	run_mlx_loop(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &loop_full, fdf);
	mlx_loop(fdf->mlx);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
}

static void	setup_event_hooks(t_fdf *fdf)
{
	clear_keys(fdf->keys, 0);
	mlx_hook(fdf->win, 2, 1L << 0, &key_press, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, &key_release, fdf);
	mlx_hook(fdf->win, 17, 0, &close_window, fdf);
	image_view(fdf);
}

static t_fdf	*init_prog(char *mapname)
{
	static t_fdf	fdf;

	fdf.map = parse_map(mapname);
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
	{
		free_map(fdf.map);
		error_exit("Failed to initialize mlx");
	}
	fdf.win = NULL;
	fdf.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.img)
	{
		free_map(fdf.map);
		error_exit("Failed to create image");
	}
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_len, &fdf.endian);
	if (!fdf.addr)
		error_exit("Failed to get data address");
	return (&fdf);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2 || !valid_map(av[1]))
		error_exit("Usage: ./fdf <map.fdf>");
	fdf = init_prog(av[1]);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH,
			HEIGHT, "the fdf of Y   K   Y ' s");
	if (!fdf->win)
	{
		free_map(fdf->map);
		mlx_destroy_image(fdf->mlx, fdf->img);
		error_exit("Failed to create window");
	}
	setup_event_hooks(fdf);
	if (mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0) == -1)
	{
		free_map(fdf->map);
		mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_image(fdf->mlx, fdf->img);
		error_exit("Failed to put image to window");
	}
	run_mlx_loop(fdf);
	return (free_map(fdf->map), free(fdf->mlx), 0);
}
