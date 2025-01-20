/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keycode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 04:49:51 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/20 08:10:57 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (keycode >= 0 && keycode <= KEY_MAX)
		fdf->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (keycode >= 0 && keycode <= KEY_MAX)
		fdf->keys[keycode] = 0;
	return (0);
}

void	clear_keys(int *keys, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		keys[i] = 0;
		i++;
	}
}