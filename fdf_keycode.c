/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keycode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 04:49:51 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/15 06:05:03 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, void *win)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)win;
	if (keycode >= 0 && keycode < 34)
		fdf->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, void *win)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)win;
	if (keycode >= 0 && keycode < 34)
		fdf->keys[keycode] = 0;
	return (0);
}
void	clear_keys(int *keys, int index)
{
	if (index >= 34)
		return ;
	keys[index] = 0;
	clear_keys(keys, index + 1);
}
