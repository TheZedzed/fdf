/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharvet <tcharvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:18:51 by tcharvet          #+#    #+#             */
/*   Updated: 2021/08/13 16:11:55 by tcharvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	set_zoom_shift_and_z(t_fdf *fdf)
{
	float	zoomy;
	float	zoomx;

	zoomx = 1920 / (fdf->width - 1);
	zoomy = 1080 / (fdf->height - 1);
	fdf->zoom = fminf(zoomx, zoomy) / ((fmaxf(fdf->width, fdf->height)
				/ fminf(fdf->width, fdf->height)) * 2);
	if (fdf->zoom < 0)
		fdf->zoom = 0;
	fdf->shift_x = (1920 - (fdf->zoom * (fdf->width - 1))) / 2 ;
	fdf->shift_y = (1080 - (fdf->zoom * (fdf->height - 1))) / 2 ;
	fdf->z_depth = 2;
}

static int	new_image(t_fdf *el)
{
	t_mlx	*mlx;
	int		err;
	int		bpp;
	int		l;
	int		e;

	err = 1;
	mlx = el->mlx;
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (mlx->img)
	{
		img->addr = (int *)mlx_get_data_addr(mlx->img, &bpp, &l, &e);
		mlx->w = 1920;
		mlx->h = 1080;
		err = 0;
	}
	return (err);
}

int	init(t_fdf *el)
{
	t_mlx	*mlx;
	int		err;

	err = 1;
	el = ft_calloc(1, sizeof(t_fdf));
	if (el)
	{
		el->mlx = ft_calloc(1, sizeof(t_mlx));
		if (el->mlx)
		{
			mlx = el->mlx;
			mlx->mlx_ptr = mlx_init();
			if (mlx->mlx_ptr)
			{
				mlx->win_ptr = mlx_nex_window(mlx->mlx_ptr, 1920, 1080, "fdf");
				if (mlx->win_ptr)
					return (new_image(fdf));
			}
		}
	}
	return (err);
}
