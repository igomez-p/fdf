/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:27:07 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 18:41:45 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	is_empty(t_cub *c, int x, int y)
{
	if (x < 0 || y < 0 || x >= c->nrows)
		return (1);
	return (((int)c->map[x][y] >= 9 && (int)c->map[x][y] <= 13)
		|| c->map[x][y] == SPACE || !c->map[x][y]);
}

void	check_map_wall(t_cub *c)
{
	int	x;
	int	y;

	x = -1;
	while (c->map[++x])
	{
		y = -1;
		while (c->map[x][++y])
		{
			if (c->map[x][y] == EMPTY || c->map[x][y] == OBJECT
				|| c->map[x][y] == NORTH || c->map[x][y] == SOUTH
				|| c->map[x][y] == WEST || c->map[x][y] == EAST)
			{
				if (is_empty(c, x - 1, y - 1) || is_empty(c, x - 1, y)
					|| is_empty(c, x - 1, y + 1) || is_empty(c, x, y - 1)
					|| is_empty(c, x, y + 1) || is_empty(c, x + 1, y - 1)
					|| is_empty(c, x + 1, y) || is_empty(c, x, y + 1))
				{
					if (c->map[x][y] == EMPTY || c->map[x][y] == OBJECT)
						clean_exit(c, "Map must be surrounded by walls\n", 1);
					clean_exit(c, "The player must be inside the map\n", 1);
				}
			}
		}
	}
}
