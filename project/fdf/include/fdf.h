/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:56:55 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/07 19:56:57 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define Z_DEPTH 2

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*addr;
}t_mlx;

typedef struct s_point
{
	int	color;
	int	z;
}t_point;

typedef struct s_fdf
{
	t_mlx	*mlx;
	t_point	**map;
	float	zoom;
	int		width;
	int		height;
	int		shift_x;
	int		shift_y;
}t_fdf;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	x1;
	float	y1;
}t_coordinates;

void		free_split(char **line);
int			parse(t_fdf *el, char *filename);
int			init(t_fdf **el, int ac, char *filename);
int			manage_heap(int end, void *addr, t_fdf *el);
void		bresenham_algo(t_coordinates pts, t_fdf *el);
#endif
