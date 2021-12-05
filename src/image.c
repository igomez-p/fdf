/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/05 14:43:38 by igomez-p         ###   ########.fr       */
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
		return (0x0000ff);
	else if (z <= (data->r.min + 2 * i))
		return (0xff00ff);
	else if (z <= (data->r.min + 3 * i))
		return (0xffffff);
	else if (z <= (data->r.min + 4 * i))
		return (0x00ff00);
	else if (z <= (data->r.min + 5 * i))
		return (0xff0000);
	else if (z <= (data->r.min + 6 * i))
		return (0xffff00);
	return (0);
}

int		display_img(t_fdf *d)
{
	t_point	p;
	int		color;

	p.y = 0;
	while (p.y < d->nrows)
	{
		p.x = 0;
		while (p.x < d->ncols)
		{
			color = set_color(p.x, p.y, d);
			if (p.x < d->ncols - 1)
				plotline(p, p.x + 1, p.y, d, color);
			if (p.y < d->nrows - 1)
				plotline(p, p.x, p.y + 1, d, color);
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(d->libx.mlx, d->libx.window, d->win.img, 0, 0);
	return (1);
}
