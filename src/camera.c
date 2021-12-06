/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:06:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 11:45:28 by igomez-p         ###   ########.fr       */
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
	data->cam.angle = ANGLE;
	data->cam.pangle = PERSPECTIVE_ANGLE;
	data->cam.isometric = ISOMETRIC;
	data->cam.plane = PLANE;
	data->cam.oblique = OBLIQUE;
	data->cam.zoom = zoom(data->ncols);
	data->cam.x = WID_TAM / 3 + 100;
	data->cam.y = HEI_TAM / 2;
	data->cam.rotate[0] = 0;
	data->cam.rotate[1] = 0;
	data->cam.rotate[2] = 0;
}
