/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:06:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/05 19:21:00 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	perform_zoom(t_point *p0, t_point *p1, int z[2], t_fdf *data)
{
	p0->x *= data->cam.zoom;
	p0->y *= data->cam.zoom;
	p1->x *= data->cam.zoom;
	p1->y *= data->cam.zoom;
	z[0] *= data->cam.zoom / 2;
	z[1] *= data->cam.zoom / 2;
}

void	perform_position(t_point *p0, t_point *p1, t_fdf *data)
{
	p0->x += data->cam.x;
	p0->y += data->cam.y;
	p1->x += data->cam.x;
	p1->y += data->cam.y;
}

int	zoom(int size)
{
	if (size <= 20)
		return (ZOOM);
	else if (size <= 50)
		return (ZOOM / 2);
	else if (size < 150)
		return (ZOOM / 4);
	else
		return (2);
}

void	range(t_fdf *data)
{
	int		x;
	int		y;

	y = 0;
	data->r.max = __INT_MAX__ * -1;
	data->r.min = __INT_MAX__;
	while (y < data->nrows)
	{
		x = 0;
		while (x < data->ncols)
		{
			if (data->map[y][x] < data->r.min)
				data->r.min = data->map[y][x];
			if (data->map[y][x] > data->r.max)
				data->r.max = data->map[y][x];
			x++;
		}
		y++;
	}
	data->r.range = abs(data->r.max - data->r.min);
}

void	init_cam(t_fdf *data)
{
	range(data);
	data->cam.angle = 0.1;
	data->cam.pangle = 0.53;
	data->cam.isometric = 1;
	data->cam.plane = 0;
	data->cam.oblique = 0;
	data->cam.zoom = zoom(data->ncols);
	data->cam.x = WID_TAM / 3 + 100;
	data->cam.y = HEI_TAM / 2;
	data->cam.rotate[0] = 0;
	data->cam.rotate[1] = 0;
	data->cam.rotate[2] = 0;
}

void	rotation(int *a, int *b, double angle, int plane)
{
	int pre_a;
	int pre_b;

	pre_a = *a;
	pre_b = *b;
	*a = pre_a * cos(angle) + pre_b * sin(angle);
	if (plane == ROT_Z)
		*a = pre_a * cos(angle) - pre_b * sin(angle);
	*b = -pre_a * sin(angle) + pre_b * cos(angle);
	if (plane == ROT_Z)
		*b = pre_a * sin(angle) + pre_b * cos(angle);

}

void	rotate(int *x, int *y, int *z, t_fdf *data)
{
	if (data->cam.rotate[0])
		rotation(y, z, data->cam.angle, ROT_X);
	if (data->cam.rotate[1])
		rotation(x, z, data->cam.angle, ROT_Y);
	if (data->cam.rotate[2])
		rotation(x, y, data->cam.angle, ROT_Z);
}
