/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 15:31:45 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	my_mlx_pixel_put(t_fdf *c, int x, int y, int color)
{
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

/*static void	put_controls(void *addr, void *window)
{
	mlx_string_put(addr, window, 200 / 4, 50, COLOR_3, "CONTROLS");
	mlx_string_put(addr, window, 200 / 4, 55, COLOR_1, "________");
	mlx_string_put(addr, window, 200 / 4, 80, COLOR_3, "Zoom: Scroll");
	mlx_string_put(addr, window, 200 / 4, 100, COLOR_3, "Move");
	mlx_string_put(addr, window, 200 / 4, 105, COLOR_1, "____");
	mlx_string_put(addr, window, 200 / 4, 130, COLOR_3, "W -> Up");
	mlx_string_put(addr, window, 200 / 4, 150, COLOR_1, "S -> Down");
	mlx_string_put(addr, window, 200 / 4, 170, COLOR_3, "A -> Left");
	mlx_string_put(addr, window, 200 / 4, 190, COLOR_3, "D -> Right");
	mlx_string_put(addr, window, 200 / 4, 220, COLOR_3, "Projection");
	mlx_string_put(addr, window, 200 / 4, 225, COLOR_1, "__________");
	mlx_string_put(addr, window, 200 / 4, 250, COLOR_3, "ISO -> I");
	mlx_string_put(addr, window, 200 / 4, 270, COLOR_3, "PLAN -> P");
	mlx_string_put(addr, window, 200 / 4, 290, COLOR_3, "OBLIQUE -> O");
	mlx_string_put(addr, window, 200 / 4, 320, COLOR_3, "Rotation: Arrows");
	mlx_string_put(addr, window, 200 / 4, 325, COLOR_1, "________________");
	mlx_string_put(addr, window, 200 / 4, 350, COLOR_3, "Left -> X Axis");
	mlx_string_put(addr, window, 200 / 4, 370, COLOR_3, "Right -> Y Axis");
	mlx_string_put(addr, window, 200 / 4, 390, COLOR_3, "Up -> Z Axis");
	mlx_string_put(addr, window, 200 / 4, 410, COLOR_3, "Down -> Reset");
}*/

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
	printf("hola\n");
	//put_controls(d->win.addr, d->libx.window);
	printf("en medio\n");
	mlx_mouse_hook(d->libx.window, zoom_bonus, d);
	printf("adios\n");
	return (1);
}
