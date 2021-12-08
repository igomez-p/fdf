/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:24:00 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/08 10:58:36 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	cam_mov(int key, t_fdf *data)
{
	if (key == KEY_LEFT)
		data->cam.rotate[0] = 1;
	if (key == KEY_RIGHT)
		data->cam.rotate[1] = 1;
	if (key == KEY_UP)
		data->cam.rotate[2] = 1;
	if (key == KEY_DOWN)
	{
		data->cam.rotate[0] = 0;
		data->cam.rotate[1] = 0;
		data->cam.rotate[2] = 0;
		data->cam.angle = 0;
	}
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP)
		data->cam.angle += ANGLE;
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
		data->mov = 1;
}

int	zoom_bonus(int button, int x, int y, t_fdf *c)
{
	x++;
	y++;
	if (button == M_SCR_U && c->cam.zoom)
		c->cam.zoom += 1;
	if (button == M_SCR_D && c->cam.zoom)
		c->cam.zoom -= 1;
	if (!c->cam.zoom)
		c->cam.zoom = 1;
	if ((button == M_SCR_U || button == M_SCR_D) && c->cam.zoom)
	{
		mlx_destroy_image(c->libx.mlx, c->win.img);
		c->win.img = mlx_new_image(c->libx.mlx, c->win.wid, c->win.hei);
		if (!c->win.img)
			clean_exit(c, "When creating a new image\n", 1);
		c->win.addr = (int *)mlx_get_data_addr(c->win.img, &c->win.bpp,
				&c->win.sz, &c->win.endian);
		display_img(c);
	}
	return (0);
}

void	hooks_perspective(t_fdf *data, int key)
{
	if (key == KEY_I)
	{
		data->cam.isometric = ISOMETRIC;
		data->cam.plane = PLANE;
		data->cam.oblique = OBLIQUE;
		data->cam.pangle = PERSPECTIVE_ANGLE;
	}
	if (key == KEY_P)
	{
		data->cam.plane = PLANE1;
		data->cam.isometric = ISOMETRIC0;
		data->cam.oblique = OBLIQUE;
	}
	if (key == KEY_O)
	{
		data->cam.plane = PLANE;
		data->cam.isometric = ISOMETRIC0;
		data->cam.oblique = OBLIQUE1;
		data->cam.pangle = PERSPECTIVE_ANGLE2;
	}
	if (key == KEY_P || key == KEY_O || key == KEY_I)
		data->mov = 1;
}

static void	rotation(int *a, int *b, double angle, int plane)
{
	int	pre_a;
	int	pre_b;

	pre_a = *a;
	pre_b = *b;
	if (plane == ROT_Z)
	{
		*a = pre_a * cos(angle) - pre_b * sin(angle);
		*b = -pre_a * sin(angle) + pre_b * cos(angle);
	}
	else
	{
		*a = pre_a * cos(angle) + pre_b * sin(angle);
		*b = pre_a * sin(angle) + pre_b * cos(angle);
	}
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
