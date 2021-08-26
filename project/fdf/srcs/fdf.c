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

#include "ft_fdf.h"

void	bresenham_algo(t_coordinates coord, t_fdf *fdf)
{
	t_point	origin;
	t_point	end;
	float	x_step;
	float	y_step;
	int		max;

	origin = fdf->map[(int)coord.y][(int)coord.x];
	end = fdf->map[(int)coord.y1][(int)coord.x1];
	zoom_coord(&coord, fdf->zoom);
	iso(&coord.x, &coord.y, origin.z, fdf->z_depth);
	iso(&coord.x1, &coord.y1, end.z, fdf->z_depth);
	shift_coord(&coord, fdf->shift_x, fdf->shift_y);
	calc_step_and_max(&x_step, &y_step, &max, coord);
	while ((int)(coord.x - coord.x1) || (int)(coord.y - coord.y1))
	{
		my_mlx_pixel_put(fdf->mlx->img, coord.x, coord.y, origin.color);
		coord.x += x_step;
		coord.y += y_step;
	}
}

int	main_loop(t_fdf *fdf)
{
	unsigned int	y;
	unsigned int	x;
	t_mlx			*mlx;

	y = 0;
	mlx = fdf->mlx;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (x < fdf->width - 1)
				bresenham_algo((t_coordinates){x, y, x + 1, y}, fdf);
			if (y < fdf->height - 1)
				bresenham_algo((t_coordinates){x, y, x, y + 1}, fdf);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, fdf->mlx->img->img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		quit(fdf, 0);
	return (0);
}

int	wrong_arg(int ac, char *filename)
{
	static char	*err_arg = "Wrong number of arguments\n";
	static char *err_fdf = "Argument must be a file in format: *.fdf\n";
	size_t		len;

	if (ac == 2)
	{
		len = ft_strlen(filename);
		if (len > 4 && !ft_strcmp(&filename[len - 4], ".fdf"))
			return (0);
		else
			write(2, err_fdf, 41);
	}
	else
		write(2, err_arg, 26);
	return (1);
}

void	manage_heap(int type, void *addr, int *err)
{
	static t_list	*heap;
	t_list			*new;

	if (type == END)
		ft_lstclear(&heap, free);
	else if (!addr)
		*err = type;
	else
	{
		new = ft_lstnew(addr);
		if (!new)
			*err = SAVER;
		else
			ft_lstadd_back(&heap, new);
	}
}

int	wrong_file(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putstr_fd("Arg must be a map file not a directory\n", 2);
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	return (fd);
}

int	main(int ac, char **av)
{
	t_fdf	*el;
	int		err;

	err = 0;
	el = NULL;
	if (!init(el) && !wrong_arg(el))
	{
		fdf.fd = check_file(av[1]);
		if (!parse(&fdf, 0))
		{
			close(fdf.fd);
			set_zoom_shift_and_z(&fdf);
			mlx.img = &img;
			init_mlx(&mlx, &fdf);
			mlx_loop_hook(mlx.ptr, &main_loop, &fdf);
			mlx_hook(mlx.win_ptr, 2, (1L << 0), &key_press, &fdf);
			mlx_loop(mlx.ptr);
		}
	}
	manage_heap(END, NULL, &err);
	return (err);
}
