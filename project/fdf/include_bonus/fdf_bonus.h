/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:35:25 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/08 15:35:33 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define ESC_KEY 0xff1b
# define ZOOM 0xffab
# define DEZOOM 0xffad
# define SHIFT_RIGHT 0xff53
# define SHIFT_LEFT 0xff51
# define SHIFT_UP 0xff54
# define SHIFT_DOWN 0xff52
# define PROJECTION 0x70
# define Z_DEPTH_MORE 0x7a
# define Z_DEPTH_LESS 0x73

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
	int		z_depth;
	int		projection;
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
