/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:18:11 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/05 13:34:10 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	resize_window(t_cub *c)
{
	if (c->res.x <= c->win.wid)
		c->win.wid = c->res.x;
	if (c->res.y <= c->win.hei)
		c->win.hei = c->res.y;
}

void	init_mlx_func(t_cub *c)
{
	c->libx.mlx = mlx_init();
	if (!c->libx.mlx)
		clean_exit(c, "MLX was not initialized\n", 1);
	mlx_get_screen_size(c->libx.mlx, &c->win.wid, &c->win.hei);
	resize_window(c);
	c->libx.window = mlx_new_window(c->libx.mlx, c->win.wid,
			c->win.hei, "Cub3D");
	if (!c->libx.window)
		clean_exit(c, "When opening a new window\n", 1);
	c->win.img = mlx_new_image(c->libx.mlx, c->win.wid, c->win.hei);
	if (!c->win.img)
		clean_exit(c, "When creating a new image\n", 1);
	c->win.addr = (int *)mlx_get_data_addr(c->win.img, &c->win.bpp, &c->win.sz,
			&c->win.endian);
	mlx_do_key_autorepeatoff(c->libx.mlx);
}
