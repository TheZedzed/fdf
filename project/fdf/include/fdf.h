#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define ESC_KEY 65536

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		*addr;
	void	*img;
	int		w;
	int		h;
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
	int		z_depth;
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

int				protect_malloc(void **ptr, size_t lenght);
char			**free_split(char **strs, int len);
char			*ft_str_tolower(char *str);

int				check_file(char *filename);
int				check_arg(int ac, char *filename);
void			set_zoom_shift_and_z(t_fdf *fdf);
void			init_mlx(t_mlx *mlx, t_fdf *fdf);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			zoom_coord(t_coordinates *coord, float zoom);
void			shift_coord(t_coordinates *coord, int shift_x, int shift_y);
int				recursive_parse(t_fdf *fdf, unsigned int len);
unsigned int	tab_len(void **tab);
int				recursive_error(char *str, char **strs,
					unsigned int len, t_fdf *fdf);
void			iso(float *x, float *y, int z, int z_value);
void			calc_step_and_max(float *x_step, float *y_step,
				int *max, t_coordinates coord);
#endif
