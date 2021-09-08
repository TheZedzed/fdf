/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:55:14 by azeraoul          #+#    #+#             */
/*   Updated: 2021/09/07 19:55:17 by azeraoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	quit(t_fdf *el)
{
	t_mlx	*mlx;

	if (el && el->mlx)
	{
		mlx = el->mlx;
		if (mlx->img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		if (mlx->win_ptr)
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		if (mlx->mlx_ptr)
		{
			mlx_destroy_display(mlx->mlx_ptr);
			free(mlx->mlx_ptr);
		}
	}
}

int	manage_heap(int end, void *addr, t_fdf *el)
{
	static t_list	*heap;
	t_list			*new;

	if (end || !addr)
	{
		quit(el);
		ft_lstclear(&heap, free);
		if (!addr && !end)
			exit(1);
		exit(0);
	}
	else
	{
		new = ft_lstnew(addr);
		if (!new)
			manage_heap(1, NULL, el);
		ft_lstadd_back(&heap, new);
	}
	return (0);
}

void	free_split(char **line)
{
	int	len;

	len = 0;
	if (line)
	{
		while (line[len])
		{
			free(line[len]);
			++len;
		}
		free(line);
	}
}
