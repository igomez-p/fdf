/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:31:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 16:31:49 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/*static int	rgb2int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}*/

void	my_mlx_pixel_put(t_cub *c, int x, int y, int color)
{
	c->win.addr[c->win.wid * y + x] = color;
}

void	free_map(t_cub *c)
{
	int	i;

	i = c->nrows;
	if (c->map)
	{
		while (i >= 0)
		{
			free(c->map[i]);
			c->map[i] = NULL;
			i--;
		}
		free(c->map);
		c->map = NULL;
	}
}
