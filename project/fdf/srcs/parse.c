#include "fdf.h"

static int	good_line(t_fdf *el, char **line)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	if (line)
	{
		manage_heap(0, line, el);
		while (line[++i])
		{
			manage_heap(0, line[i], el);
			++len;
		}
		if (!el->width)
			el->width = len;
		if (len == el->width)
			return (1);
	}
	return (0);
}

static void	fill_color(t_point *point, char *line)
{
	char	*color;
	int		i;

	color = ft_strchr(line, ',');
	if (color && ++color)
	{
		if (!ft_strncmp(color, "0x", 2))
		{
			i = -1;
			while (color[++i])
				ft_tolower(color[i]);
			point->color = ft_atoi_base(color + 2, "0123456789abcdef");
		}
		else
			point->color = ft_atoi(color);
	}
	if (!color || !point->color)
		point->color = 0x00ffffff;
}

static int	create_line(t_fdf *el, char *str)
{
	static int	index = 0;
	char		**line;
	int			i;

	line = ft_split(str, ' ');
	if (good_line(el, line))
	{
		i = 0;
		el->map[index] = ft_calloc(el->width, sizeof(t_point));
		manage_heap(0, el->map[index], el);
		while (line[i])
		{
			el->map[index][i].z = ft_atoi(line[i]);
			fill_color(&el->map[index][i], line[i]);
			++i;
		}
		++index;
		return (1);
	}
	return (0);
}

static int	create_map(t_fdf *el, int fd)
{
	char	*str;
	int		i;

	i = 1;
	str = NULL;
	while (i)
	{
		i = get_next_line(fd, &str);
		if (i == -1)
			return (0);
		else if (*str)
			++el->height;
		free(str);
	}
	el->map = ft_calloc(el->height, sizeof(t_point *));
	manage_heap(0, el->map, el);
	close(fd);
	return (1);
}

int	parse(t_fdf *el, char *filename)
{
	char	*str;
	int		fd;
	int		i;

	i = 1;
	str = NULL;
	fd = open(filename, O_RDONLY);
	if (fd != 1)
	{
		if (create_map(el, fd))
		{
			fd = open(filename, O_RDONLY);
			while (i)
			{
				i = get_next_line(fd, &str);
				if (i == -1 || (*str && !create_line(el, str)))
				{
					close(fd);
					return (1);
				}
			}
			close(fd);
			return (0);
		}
	}
	return (1);
}
