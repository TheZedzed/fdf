/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:33:39 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/09 15:51:36 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	color_(int col1, int col2, float ratio)
{
	int	a[3];
	int	b[3];
	int	c[3];
	int	color;

	a[0] = (col2 >> 16);
	a[1] = (col2 >> 8);
	a[2] = col2;
	b[0] = (col1 >> 16);
	b[1] = (col1 >> 8);
	b[2] = col1;
	c[0] = a[0] + (a[0] - b[0]) * ratio;
	c[1] = a[1] + (a[1] - b[1]) * ratio;
	c[2] = a[2] + (a[2] - b[2]) * ratio;
	color = (c[0] << 16) | (c[1] << 8) | c[2];
	return (color);
}

static void	init_steps_utils(t_coordinates *pts, float *steps, int *utils)
{
	utils[1] = 0;
	steps[0] = (pts->x1 - pts->x);
	steps[1] = (pts->y1 - pts->y);
	utils[0] = fmaxf(fabsf(steps[0]), fabsf(steps[1]));
	steps[0] /= utils[0];
	steps[1] /= utils[0];
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

static void	isometric(t_coordinates *pts, t_fdf *el, int *z, int *z1)
{
	int		ratio1;
	int		ratio2;
	float	temp;

	ratio1 = (*z * el->z_depth);
	ratio2 = (*z1 * el->z_depth);
	zoom_or_shift(el, pts, 1);
	if (!el->projection)
	{
		temp = pts->x;
		pts->x -= pts->y;
		pts->y = ((temp + pts->y) / 2) - ratio1;
		temp = pts->x1;
		pts->x1 -= pts->y1;
		pts->y1 = ((temp + pts->y1) / 2) - ratio2;
	}
	else
	{
		pts->y -= ratio1;
		pts->y1 -= ratio2;
	}
	zoom_or_shift(el, pts, 0);
}

void	bresenham_algo(t_coordinates pts, t_fdf *el)
{
	float	steps[2];
	int		utils[2];
	t_point	org;
	t_point	end;
	int		*ptr;

	org = el->map[(int)pts.y][(int)pts.x];
	end = el->map[(int)pts.y1][(int)pts.x1];
	isometric(&pts, el, &org.z, &end.z);
	init_steps_utils(&pts, steps, utils);
	while ((int)(pts.x - pts.x1) || (int)(pts.y - pts.y1))
	{
		if (pts.x >= 0 && pts.y >= 0 && pts.x < 1920 && pts.y < 1080)
		{
			ptr = (el->mlx->addr + ((int)pts.y * 1920 + (int)pts.x));
			if (org.color != end.color && utils[1])
				*ptr = color_(org.color, end.color, utils[0] / utils[1]);
			else
				*ptr = org.color;
		}
		pts.x += steps[0];
		pts.y += steps[1];
		++utils[1];
	}
}
