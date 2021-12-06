/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:19:02 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 12:54:25 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	key_press_handler(int key, t_fdf *c)
{
	if (key == (int)KEY_ESCAPE)
		exit_handler(c);
	return (1);
}

int	key_release_handler(int key, t_fdf *c)
{
	if (key == (int)KEY_ESCAPE)
		exit_handler(c);
	return (1);
}

int	exit_handler(t_fdf *c)
{
	clean_exit(c, "Closing program...\n", 0);
	return (0);
}

void	free_map(t_fdf *c)
{
	int	i;

	i = c->nrows - 1;
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

void	clean_exit(t_fdf *c, char *str, int error)
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
		if (c->win.img)
			mlx_destroy_image(c->libx.mlx, c->win.img);
		if (c->libx.window)
			mlx_destroy_window(c->libx.mlx, c->libx.window);
		free_map(c);
		if (c->line)
			free(c->line);
		if (c->read.l)
			free(c->read.l);
		if (c->read.b)
			free(c->read.b);
	}
	exit(1);
}
