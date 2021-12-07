/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/07 06:15:27 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	my_mlx_pixel_put(t_fdf *c, int x, int y, int color)
{
	if (x >= WID_TAM || x < 0 || y >= HEI_TAM || y < 0)
		return ;
	c->win.addr[c->win.wid * y + x] = color;
}

int	set_color(int x, int y, t_fdf *data)
{
	int		z;
	float	i;

	z = data->map[y][x];
	i = (float)data->r.range / 6;
	if (z <= data->r.min + i)
		return (COLOR_1);
	else if (z <= (data->r.min + 2 * i))
		return (COLOR_2);
	else if (z <= (data->r.min + 3 * i))
		return (COLOR_3);
	else if (z <= (data->r.min + 4 * i))
		return (COLOR_4);
	else if (z <= (data->r.min + 5 * i))
		return (COLOR_5);
	else if (z <= (data->r.min + 6 * i))
		return (COLOR_6);
	return (0);
}

static void	put_controls(void *mlx, void *window)
{
	int	x;

	x = 200 / 4;
	mlx_string_put(mlx, window, x, 40, COLOR_3, "CONTROLS");
	mlx_string_put(mlx, window, x, 45, COLOR_1, "________");
	mlx_string_put(mlx, window, x, 70, COLOR_5, "Zoom: Scroll");
	mlx_string_put(mlx, window, x, 100, COLOR_5, "Move");
	mlx_string_put(mlx, window, x, 105, COLOR_1, "____");
	mlx_string_put(mlx, window, x, 130, COLOR_3, "W -> Up");
	mlx_string_put(mlx, window, x, 150, COLOR_3, "S -> Down");
	mlx_string_put(mlx, window, x, 170, COLOR_3, "A -> Left");
	mlx_string_put(mlx, window, x, 190, COLOR_3, "D -> Right");
	mlx_string_put(mlx, window, x, 220, COLOR_5, "Projection");
	mlx_string_put(mlx, window, x, 225, COLOR_1, "__________");
	mlx_string_put(mlx, window, x, 250, COLOR_3, "I -> Isometric");
	mlx_string_put(mlx, window, x, 270, COLOR_3, "P -> Plane");
	mlx_string_put(mlx, window, x, 290, COLOR_3, "O -> Oblique");
	mlx_string_put(mlx, window, x, 320, COLOR_5, "Rotation: Arrows");
	mlx_string_put(mlx, window, x, 325, COLOR_1, "________________");
	mlx_string_put(mlx, window, x, 350, COLOR_3, "Left -> X Axis");
	mlx_string_put(mlx, window, x, 370, COLOR_3, "Right -> Y Axis");
	mlx_string_put(mlx, window, x, 390, COLOR_3, "Up -> Z Axis");
	mlx_string_put(mlx, window, x, 410, COLOR_3, "Down -> Reset");
}

int	display_img(t_fdf *d)
{
	t_point	p;

	p.y = 0;
	while (p.y < d->nrows)
	{
		p.x = 0;
		while (p.x < d->ncols)
		{
			d->color = set_color(p.x, p.y, d);
			if (p.x < d->ncols - 1)
				plotline(p, p.x + 1, p.y, d);
			if (p.y < d->nrows - 1)
				plotline(p, p.x, p.y + 1, d);
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(d->libx.mlx, d->libx.window, d->win.img, 0, 0);
	put_controls(d->libx.mlx, d->libx.window);
	mlx_mouse_hook(d->libx.window, zoom_bonus, d);
	return (1);
}
