/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:06:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/05 14:12:14 by igomez-p         ###   ########.fr       */
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

void	init_cam(t_fdf *data)
{
	data->map.range = range(data);
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
