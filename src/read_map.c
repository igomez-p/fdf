/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:25:18 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 20:24:18 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	open_map(char *filename, t_cub *info)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(info, "Fdf file could not be opened\n", 1);
	return (fd);
}

static int	array_length(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (-1);
	while (array[i])
		i++;
	return (i);
}

static int	double_free(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (-1);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

static int	*get_wh(char *filename, t_cub *info)
{
	int		*wh;
	int		fd;
	char	**buffer;

	wh = malloc(sizeof(int) * 2);
	wh[1] = 0;
	fd = open_map(filename, info);
	while (get_next_line(fd, &info->line))
	{
		buffer = ft_split(info->line, ' ');
		wh[0] = array_length(buffer);
		wh[1]++;
		free(info->line);
		double_free(buffer);
	}
	free(info->line);
	close(fd);
	return (wh);
}

static void	fill(char *line, int *map_line)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = ft_split(line, ' ');
	while (buffer[i])
	{
		map_line[i] = ft_atoi(buffer[i]);
		i++;
	}
	free(buffer);
}

void	parse_map(char *filename, t_cub *map)
{
	int		i;
	int		*wh;
	int		fd;

	i = 0;
	wh = get_wh(filename, map);
	map->ncols = wh[0];
	map->nrows = wh[1];
	free(wh);
	fd = open_map(filename, map);
	map->map = (int **)malloc(sizeof(int *) * map->nrows);
	while (i < map->nrows)
	{
		map->map[i] = (int *)malloc(sizeof(int) * map->ncols);
		i++;
	}
	i = 0;
	while ((get_next_line(fd, &map->line)) > 0)
	{
		fill(map->line, map->map[i++]);
		free(map->line);
	}
	close(fd);
	free(map->line);
}
