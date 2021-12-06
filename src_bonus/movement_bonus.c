/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:24:00 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 12:29:58 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	cam_mov(int keycode, t_fdf *data)
{
	if (keycode == K_LEFT)
		data->cam.rotate[0] = 1;
	if (keycode == K_RIGHT)
		data->cam.rotate[1] = 1;
	if (keycode == K_UP)
		data->cam.rotate[2] = 1;
	if (keycode == K_DOWN)
	{
		data->cam.rotate[0] = 0;
		data->cam.rotate[1] = 0;
		data->cam.rotate[2] = 0;
		data->cam.angle = 0;
	}
	if (keycode == K_LEFT || keycode == K_RIGHT || keycode == K_UP)
		data->cam.angle += ANGLE;
}

int	zoom_bonus(int button, int x, int y, t_fdf *data)
{
	x++;
	y++;
	if (button == M_SCR_U && data->cam.zoom)
		data->cam.zoom += 1;
	if (button == M_SCR_D && data->cam.zoom)
		data->cam.zoom -= 1;
	if (!data->cam.zoom)
		data->cam.zoom = 1;
	new_image(data);
	return (0);
}

void	hooks_perspective(t_fdf *data, int keycode)
{
	if (keycode == K_I)
	{
		data->cam.isometric = ISOMETRIC;
		data->cam.plane = PLANE;
		data->cam.oblique = OBLIQUE;
		data->cam.pangle = PERSPECTIVE_ANGLE;
	}
	if (keycode == K_P)
	{
		data->cam.plane = PLANE1;
		data->cam.isometric = ISOMETRIC0;
		data->cam.oblique = OBLIQUE;
	}
	if (keycode == K_O)
	{
		data->cam.plane = PLANE;
		data->cam.isometric = ISOMETRIC0;
		data->cam.oblique = OBLIQUE1;
		data->cam.pangle = PERSPECTIVE_ANGLE2;
	}
}