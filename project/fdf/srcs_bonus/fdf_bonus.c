/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:33:54 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/08 15:35:04 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	set_zoom_shift_and_z(t_fdf *el)
{
	float	zoomy;
	float	zoomx;
	float	ratio;

	zoomx = 1920 / (el->width - 1);
	zoomy = 1080 / (el->height - 1);
	ratio = fmaxf(el->width, el->height) / fminf(el->width, el->height) * 2;
	el->zoom = fminf(zoomx, zoomy) / ratio;
	if (el->zoom < 0)
		el->zoom = 0;
	el->shift_x = (1920 - (el->zoom * (el->width - 1))) / 2;
	el->shift_y = (1080 - (el->zoom * (el->height - 1))) / 2;
	el->z_depth = 2;
}

static int	main_loop(t_fdf *el)
{
	t_mlx	*mlx;
	int		y;
	int		x;

	y = 0;
	mlx = el->mlx;
	while (y < el->height)
	{
		x = 0;
		while (x < el->width)
		{
			if (x < el->width - 1)
				bresenham_algo((t_coordinates){x, y, x + 1, y}, el);
			if (y < el->height - 1)
				bresenham_algo((t_coordinates){x, y, x, y + 1}, el);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (0);
}

static int	key_press(int keycode, t_fdf *el)
{
	if (keycode == ESC_KEY)
		manage_heap(1, NULL, el);
	else if (keycode == ZOOM)
		el->zoom += 1;
	else if (keycode == DEZOOM && el->zoom - 1 > 0)
		el->zoom -= 1;
	else if (keycode == PROJECTION)
		el->projection = !el->projection;
	else if (keycode == SHIFT_UP)
		el->shift_y += 10;
	else if (keycode == SHIFT_DOWN)
		el->shift_y -= 10;
	else if (keycode == SHIFT_LEFT)
		el->shift_x -= 10;
	else if (keycode == SHIFT_RIGHT)
		el->shift_x += 10;
	else if (keycode == Z_DEPTH_MORE)
		el->z_depth += 1;
	else if (keycode == Z_DEPTH_LESS)
		el->z_depth -= 1;
	else
		return (0);
	ft_memset(el->mlx->addr, 0, sizeof(int) * 1920 * 1080);
	main_loop(el);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	*el;
	t_mlx	*mlx;
	int		err;

	el = NULL;
	err = init(&el, ac, av[1]);
	if (!err)
	{
		err = parse(el, av[1]);
		if (!err)
		{
			mlx = el->mlx;
			set_zoom_shift_and_z(el);
			mlx_hook(mlx->win_ptr, 2, (1L << 0), key_press, el);
			mlx_hook(mlx->win_ptr, 12, (1L << 15), main_loop, el);
			mlx_loop(mlx->mlx_ptr);
		}
		else
			write(2, "Parse error\n", 12);
	}
	return (manage_heap(1, NULL, el));
}
