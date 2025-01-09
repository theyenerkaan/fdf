/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_locations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:08:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/01/09 22:11:37 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_location(double *y, double *z, double alpha)
{
	double	appearance_y;
	
	appearance_y = *y;
	*y = appearance_y * cos(alpha) + *z * sin(alpha);
	*z = -appearance_y * sin(alpha) + *z * cos(alpha);
}
void	y_location(double *x, double *z, double beta)
{
	double	appearance_x;
	
	appearance_x = *x;
	*x = appearance_x * cos(beta) + *z * sin(beta);
	*z = -appearance_x * sin(beta) + *z * cos(beta);
}

void	z_location(double *x, double *y, double gamma)
{
	double	appearance_x;
	
	appearance_x = *x;
	*x = appearance_x * cos(gamma) - *y * sin(gamma);
	*y = appearance_x * sin(gamma) + *y * cos(gamma);
}