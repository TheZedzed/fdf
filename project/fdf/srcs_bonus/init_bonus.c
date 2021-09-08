/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:55:51 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/07 19:55:54 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	static char	*err_fdf = "Argument must be a file in format: *.fdf\n";
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

int	init(t_fdf **el, int ac, char *filename)
{
	t_mlx	*mlx;
	int		bpp;
	int		l;
	int		e;

	*el = ft_calloc(1, sizeof(t_fdf));
	manage_heap(0, *el, *el);
	if (wrong_arg(ac, filename))
		return (1);
	(*el)->mlx = ft_calloc(1, sizeof(t_mlx));
	manage_heap(0, (*el)->mlx, *el);
	mlx = (*el)->mlx;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "fdf");
	if (!mlx->win_ptr)
		return (1);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (!mlx->img_ptr)
		return (1);
	mlx->addr = (int *)mlx_get_data_addr(mlx->img_ptr, &bpp, &l, &e);
	return (0);
}
