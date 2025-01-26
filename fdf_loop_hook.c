/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:15:06 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/26 09:59:56 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop_full(void *view)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)view;
	map_view(fdf);
	rotate_view(fdf);
	image_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 1, 1);
	set_menu(fdf);
	return (0);
}
