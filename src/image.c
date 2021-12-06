/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 07:36:20 by igomez-p         ###   ########.fr       */
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
		return (0x00ffdc);
	else if (z <= (data->r.min + 2 * i))
		return (0xff6b38);
	else if (z <= (data->r.min + 3 * i))
		return (0xffffff);
	else if (z <= (data->r.min + 4 * i))
		return (0xe23030);
	else if (z <= (data->r.min + 5 * i))
		return (0x0083ff);
	else if (z <= (data->r.min + 6 * i))
		return (0xffec00);
	return (0);
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
	return (1);
}
