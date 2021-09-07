/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 12:27:33 by azeraoul          #+#    #+#             */
/*   Updated: 2021/08/10 12:27:34 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press(int keynote, t_fdf *el)
{
	printf("ok\n");
	if (keynote == 0xff1b)
		manage_heap(1, NULL, el);
	return (0);
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
	el->shift_x = (1920 - (el->zoom * (el->width - 1))) / 2 ;
	el->shift_y = (1080 - (el->zoom * (el->height - 1))) / 2 ;
	el->z_depth = 2;
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
			mlx_hook(mlx->win_ptr, 2, (1L << 2), key_press, el);
			mlx_hook(mlx->win_ptr, 12, (1L << 15), main_loop, el);
			//mlx_hook(mlx->win_ptr, 33, (1L << 5), key_press, el);
			mlx_loop(mlx->mlx_ptr);
		}
		else
			write(2, "Parse error\n", 12);
	}
	return (manage_heap(1, NULL, el));
}
