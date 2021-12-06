/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 18:25:18 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 08:38:17 by igomez-p         ###   ########.fr       */
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

	i = array_length(array) - 1;
	if (!array)
		return (-1);
	while (i >= 0)
	{
		free(array[i]);
		array[i] = NULL;
		i--;
		printf("array[i] %p\n", array[i]);
	}
	free(array);
	array = NULL;
	printf("array %p\n", array);
	return (0);
}

static void	get_wh(char *filename, t_fdf *info)
{
	int		fd;
	char	**buffer;

	info->nrows = 0;
	buffer = NULL;
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
	printf("GET WH: buffer %p | line %p \n", buffer, info->line);
	close(fd);
}

static void	fill(char *line, int *map_line)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = NULL;
	buffer = ft_split(line, ' ');
	while (buffer[i])
	{
		map_line[i] = ft_atoi(buffer[i]);
		i++;
	}
	double_free(buffer);

	printf("FILL: buffer %p\n", buffer);
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
	printf("line %p | b %p | l %p\n", map->line, map->read.b, map->read.l);
}
