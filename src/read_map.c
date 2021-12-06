/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:25:18 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 10:55:34 by igomez-p         ###   ########.fr       */
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

static int	double_free(t_fdf *data)
{
	int	i;

	i = data->ncols - 1;
	if (!data->read.buf)
		return (-1);
	while (i >= 0)
	{
		free(data->read.buf[i]);
		data->read.buf[i] = NULL;
		i--;
	}
	free(data->read.buf);
	data->read.buf = NULL;
	return (0);
}

static void	get_wh(char *filename, t_fdf *info)
{
	int		fd;

	info->nrows = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(info, "Fdf file could not be opened\n", 1);
	while (get_next_line(fd, &info->line, &info->read.b, &info->read.l))
	{
		ft_split(info->line, ' ', info);
		info->ncols = array_length(info->read.buf);
		info->nrows++;
		double_free(info);
		free(info->line);
		info->line = NULL;
	}
	free(info->line);
	info->line = NULL;
	close(fd);
}

static void	fill(char *line, int *map_line, t_fdf *data)
{
	int		i;

	i = 0;
	ft_split(line, ' ', data);
	while (data->read.buf[i])
	{
		map_line[i] = ft_atoi(data->read.buf[i]);
		i++;
	}
	double_free(data);
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
		fill(map->line, map->map[i++], map);
		free(map->line);
		map->line = NULL;
	}
	close(fd);
}
