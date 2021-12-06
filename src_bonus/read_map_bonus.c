/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:25:18 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/05 18:51:09 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (0);
}

static void	get_wh(char *filename, t_fdf *info)
{
	int		fd;
	char	**buffer;

	info->nrows = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(info, "Fdf file could not be opened\n", 1);
	while (get_next_line(fd, &info->line, &info->read.b, &info->read.l))
	{
		buffer = ft_split(info->line, ' ');
		info->ncols = array_length(buffer);
		info->nrows++;
		free(info->line);
		info->line = NULL;
		double_free(buffer);
	}
	free(info->line);
	info->line = NULL;
	close(fd);
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
	double_free(buffer);
}

void	parse_map(char *filename, t_fdf *map)
{
	int		i;
	int		fd;

	i = 0;
	get_wh(filename, map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(map, "Fdf file could not be opened\n", 1);
	map->map = (int **)malloc(sizeof(int *) * map->nrows);
	while (i < map->nrows)
	{
		map->map[i] = (int *)malloc(sizeof(int) * map->ncols);
		i++;
	}
	i = 0;
	while (get_next_line(fd, &map->line, &map->read.b, &map->read.l) > 0)
	{
		fill(map->line, map->map[i++]);
		free(map->line);
		map->line = NULL;
	}
	close(fd);
	if (map->line)
	{
		free(map->line);
		map->line = NULL;
	}
}