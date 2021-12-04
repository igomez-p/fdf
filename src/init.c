/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:27:57 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 20:21:52 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	init_file_vble(t_cub *info)
{
	info->res.x = WID_TAM;
	info->res.y = HEI_TAM;
	info->line = NULL;
	info->map = NULL;
	info->r.b = NULL;
	info->r.l = NULL;
	info->r.stc = NULL;
	info->r.sizes = NULL;
}

void	init_struct(t_cub *info)
{
	init_file_vble(info);
	info->libx.mlx = NULL;
	info->libx.window = NULL;
	info->win.img = NULL;
	info->ncols = 0;
	info->nrows = 0;
	info->check.map = 0;
}
