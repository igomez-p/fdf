/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:44:00 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 12:22:35 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	isometric(int *x, int *y, int z, double angle)
{
	int	pre_x;
	int	pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = (pre_x - pre_y) * cos(angle);
	*y = (pre_x + pre_y) * sin(angle) - z;
}

static void	lowplotline(t_point p0, t_point p1, t_fdf *data)
{
	t_vbles	low;

	low.dx = p1.x - p0.x;
	low.dy = p1.y - p0.y;
	low.yi = 1;
	if (low.dy < 0)
	{
		low.yi = -1;
		low.dy = -low.dy;
	}
	low.d = (2 * low.dy) - low.dx;
	low.y = p0.y;
	while (p0.x < p1.x)
	{
		my_mlx_pixel_put(data, p0.x, low.y, data->color);
		if (low.d > 0)
		{
			low.y = low.y + low.yi;
			low.d = low.d + (2 * (low.dy - low.dx));
		}
		else
			low.d = low.d + 2 * low.dy;
		p0.x++;
	}
}

static void	highplotline(t_point p0, t_point p1, t_fdf *data)
{
	t_vbles	high;

	high.dx = p1.x - p0.x;
	high.dy = p1.y - p0.y;
	high.xi = 1;
	if (high.dx < 0)
	{
		high.xi = -1;
		high.dx = -high.dx;
	}
	high.d = (2 * high.dx) - high.dy;
	high.x = p0.x;
	while (p0.y < p1.y)
	{
		my_mlx_pixel_put(data, high.x, p0.y, data->color);
		if (high.d > 0)
		{
			high.x = high.x + high.xi;
			high.d = high.d + (2 * (high.dx - high.dy));
		}
		else
			high.d = high.d + 2 * high.dx;
		p0.y++;
	}
}

static void	auxiliar(t_point *p0, t_point *p1, int z[2], t_fdf *data)
{
	perform_zoom(p0, p1, z, data);
	rotate(&p0->x, &p0->y, &z[0], data);
	rotate(&p1->x, &p1->y, &z[1], data);
	if (data->cam.isometric || data->cam.oblique)
	{
		isometric(&p0->x, &p0->y, z[0], data->cam.pangle);
		isometric(&p1->x, &p1->y, z[1], data->cam.pangle);
	}
	perform_position(p0, p1, data);
}

void	plotline(t_point p0, int x1, int y1, t_fdf *data)
{
	int		z[2];
	t_point	p1;

	p1.x = x1;
	p1.y = y1;
	z[0] = data->map[(int)p0.y][(int)p0.x];
	z[1] = data->map[(int)p1.y][(int)p1.x];
	auxiliar(&p0, &p1, z, data);
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			lowplotline(p1, p0, data);
		else
			lowplotline(p0, p1, data);
	}
	else
	{
		if (p0.y > p1.y)
			highplotline(p1, p0, data);
		else
			highplotline(p0, p1, data);
	}
}
