#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# include "mlx.h"
# include <math.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>

# define ESC_KEY 65307 //53
# define ZOOM 61 //69
# define DEZOOM 45//78
# define SHIFT_RIGHT 65363 //124
# define SHIFT_LEFT 65361//123
# define SHIFT_UP 65362 //126
# define SHIFT_BOTTOM 65364 //125
# define PROJECTION 112 //35
# define Z_DEPTH_MORE 122 //6
# define Z_DEPTH_LESS 100 //2

typedef struct s_gnl
{
	char	*buf;
	size_t	i;
	size_t	max;
	int		y;
}			t_gnl;

typedef struct s_img {
	void	*img;
	int		*addr;
	int		bpp;
	int		line;
	int		w;
	int		h;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_img	*img;
}				t_mlx;

typedef struct s_point
{
	int	z;
	int	color;
}			t_point;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	x1;
	float	y1;
}				t_coordinates;

typedef struct s_moove
{
	int	zoom;
	int	dezoom;
	int	add_shiftx;
	int	less_shiftx;
	int	add_shifty;
	int	less_shifty;
	int	add_z_depth;
	int	less_z_depth;
}		t_moove;

typedef struct s_fdf
{
	t_mlx			*mlx;
	t_point			**map;
	t_moove			moove;
	unsigned int	width;
	unsigned int	height;
	int				fd;
	int				error_code;
	float			zoom;
	int				z_depth;
	int				shift_x;
	int				shift_y;
	int				projection;
}						t_fdf;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}						t_rgb;

int				protect_malloc(void **ptr, size_t lenght);
char			**free_split(char **strs, int len);
char			*ft_str_tolower(char *str);

float			get_abs(float i);
float			get_fmax(float a, float b);
float			get_fmin(float a, float b);
int				get_imax(int a, int b);
int				get_imin(int a, int b);

void			bresenham_algo_bonus(t_coordinates coord, t_fdf *fdf);
void			quit(t_fdf *fdf, char *err);
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
void			iso(float *x, float *y, float z, float z_depth);
void			projection_bonus(float *x, float *y, int z_tab[2],
					int projection);
void			calc_step_and_max(float *x_step, float *y_step,
					int *max, t_coordinates coord);
void			toogle(int *value);
void			adjust_values(t_fdf *fdf);
void			shift_keys(int keycode, t_moove *moove);
void			z_depth_keys(int keycode, t_moove *moove);
void			zoom_or_dezoom_key(int keycode, t_moove *moove);
#endif
