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
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (mlx->img_ptr)
	{
		img->addr = (int *)mlx_get_data_addr(mlx->img_ptr, &bpp, &l, &e);
		mlx->w = 1920;
		mlx->h = 1080;
		err = 0;
	}
	return (err);
}

static int	check_file(char *filename)
{
	int	err;
	int	fd;

	err = 1;
	fd = open(filename, O_DIRECTORY);
	if (fd == -1)
	{
		fd = open(filename, O_RDONLY);
		if (fd != -1)
			err = 0;
	}
	if (fd != -1)
		close(fd);
	if (err)
		perror("filename error");
	return (err);
}

static int	wrong_arg(int ac, char *filename)
{
	static char	*err_arg = "Wrong number of arguments\n";
	static char *err_fdf = "Argument must be a file in format: *.fdf\n";
	size_t		len;

	if (ac == 2)
	{
		len = ft_strlen(filename);
		if (len > 4 && !ft_strcmp(&filename[len - 4], ".fdf"))
			return (check_file(filename));
		else
			write(2, err_fdf, 41);
	}
	else
		write(2, err_arg, 26);
	return (1);
}

int	fail_init(t_fdf *el, int ac, char *filename)
{
	t_mlx	*mlx;
	int		err;

	err = 1;
	el = ft_calloc(1, sizeof(t_fdf));
	manage_heap(INIT, el);
	if (el && !wrong_arg(ac, filename))
	{
		el->mlx = ft_calloc(1, sizeof(t_mlx));
		manage_heap(INIT, el->mlx);
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
