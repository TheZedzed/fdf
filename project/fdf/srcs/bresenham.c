/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:53:04 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/07 19:53:06 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_steps(t_coordinates *pts, float *steps)
{
	int	max;

	steps[0] = (pts->x1 - pts->x);
	steps[1] = (pts->y1 - pts->y);
	max = fmaxf(fabsf(steps[0]), fabsf(steps[1]));
	steps[0] /= max;
	steps[1] /= max;
}

static void	zoom_or_shift(t_fdf *el, t_coordinates *coord, int zoom)
{
	if (zoom)
	{
		coord->x *= el->zoom;
		coord->y *= el->zoom;
		coord->x1 *= el->zoom;
		coord->y1 *= el->zoom;
	}
	else
	{
		coord->x += el->shift_x;
		coord->y += el->shift_y;
		coord->x1 += el->shift_x;
		coord->y1 += el->shift_y;
	}
}

static void	isometric(t_coordinates *pts, int *z, int *z1)
{
	float	temp;

	temp = pts->x;
	pts->x -= pts->y;
	pts->y = ((temp + pts->y) / 2) - (*z * Z_DEPTH);
	temp = pts->x1;
	pts->x1 -= pts->y1;
	pts->y1 = ((temp + pts->y1) / 2) - (*z1 * Z_DEPTH);
}

void	bresenham_algo(t_coordinates pts, t_fdf *el)
{
	float	steps[2];
	t_point	org;
	t_point	end;

	org = el->map[(int)pts.y][(int)pts.x];
	end = el->map[(int)pts.y1][(int)pts.x1];
	zoom_or_shift(el, &pts, 1);
	isometric(&pts, &org.z, &end.z);
	zoom_or_shift(el, &pts, 0);
	init_steps(&pts, steps);
	while ((int)(pts.x - pts.x1) || (int)(pts.y - pts.y1))
	{
		if (pts.x >= 0 && pts.y >= 0 && pts.x < 1920 && pts.y < 1080)
			*(el->mlx->addr + ((int)pts.y * 1920 + (int)pts.x)) = org.color;
		pts.x += steps[0];
		pts.y += steps[1];
	}
}
