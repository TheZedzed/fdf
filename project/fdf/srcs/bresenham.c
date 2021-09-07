#include "fdf.h"

static void	do_step(t_coordinates *pts, float *x_step, float *y_step)
{
	int	max;

	if (!*x_step && !*y_step)
	{
		*x_step = (pts->x1 - pts->x);
		*y_step = (pts->y1 - pts->y);
		max = fmaxf(fabsf(*x_step), fabsf(*y_step));
		*x_step /= max;
		*y_step /= max;
	}
	pts->x += *x_step;
	pts->y += *y_step;
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

void	bresenham_algo(t_coordinates pts, t_fdf *el)
{
	t_point	origin;
	t_point	end;
	float	temp;
	float	a;
	float	b;

	a = 0;
	b = 0;
	end = el->map[(int)pts.y1][(int)pts.x1];
	origin = el->map[(int)pts.y][(int)pts.x];
	zoom_or_shift(el, &pts, 1);
	temp = pts.x;
	pts.x -= pts.y;
	pts.y = ((temp + pts.y) / 2) - (origin.z * el->z_depth);
	temp = pts.x1;
	pts.x1 -= pts.y1;
	pts.y1 = ((temp + pts.y1) / 2) - (end.z * el->z_depth);
	zoom_or_shift(el, &pts, 0);
	while ((int)(pts.x - pts.x1) || (int)(pts.y - pts.y1))
	{
		if (pts.x >= 0 && pts.y >= 0 && pts.x < 1920 && pts.y < 1080)
			*(el->mlx->addr + ((int)pts.y * 1920 + (int)pts.x)) = origin.color;
		do_step(&pts, &a, &b);
	}
}
