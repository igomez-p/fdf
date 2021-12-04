/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:19:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 17:30:45 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	key_press_handler(int key, t_cub *c)
{
	if (key == (int)KEY_ESCAPE)
		exit_handler(c);
	return (1);
}

int	key_release_handler(int key, t_cub *c)
{
	if (key == (int)KEY_ESCAPE)
		exit_handler(c);
	return (1);
}

int	exit_handler(t_cub *c)
{
	clean_exit(c, "Closing program...\n", 0);
	return (0);
}

void	clean_exit(t_cub *c, char *str, int error)
{
	int	len;

	len = ft_strlen(str);
	if (error)
		write(1, "Error\n", 6);
	if (!str)
		perror("");
	else
		write(1, str, len);
	if (c != NULL)
	{
		if (c->libx.window)
			mlx_destroy_window(c->libx.mlx, c->libx.window);
		if (c->win.img)
			mlx_destroy_image(c->libx.mlx, c->win.img);
		if (c->line != NULL)
			free(c->line);
		if (c->r.l)
			free(c->r.l);
	}
	exit(1);
}
