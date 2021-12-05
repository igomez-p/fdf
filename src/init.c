/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:27:57 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/05 14:10:57 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	init_cam(t_fdf *info)
{
	info->cam.pangle = 0.0;
}

void	init_struct(t_fdf *info)
{
	init_cam(info);
	info->res.x = WID_TAM;
	info->res.y = HEI_TAM;
	info->line = NULL;
	info->map = NULL;
	info->libx.mlx = NULL;
	info->libx.window = NULL;
	info->win.img = NULL;
	info->win.addr = NULL;
	info->win.bpp = 0;
	info->win.endian = 0;
	info->win.sz = 0;
	info->win.wid = 0;
	info->win.hei = 0;
	info->ncols = 0;
	info->nrows = 0;

}

static void	resize_window(t_fdf *c)
{
	if (c->res.x <= c->win.wid)
		c->win.wid = c->res.x;
	if (c->res.y <= c->win.hei)
		c->win.hei = c->res.y;
}

void	init_mlx_func(t_fdf *c)
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
