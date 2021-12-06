/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:52:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 07:43:57 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static void	check_argc(t_fdf *cub, int n)
{
	if (n < 2 || n > 3)
		clean_exit(cub, "Invalid number of arguments\n", 1);
}

void	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strncmp(&filename[len - 4], ".fdf", 4) != 0)
		clean_exit(NULL, "The file extension must be .fdf\n", 1);
}

int	main(int argc, char *argv[])
{
	t_fdf	cub;

	init_struct(&cub);
	check_argc(&cub, argc);
	check_extension(argv[1]);
	parse_map(argv[1], &cub);
	/*printf("nrows %d\n\n", cub.nrows);
	for (int i = 0; i < cub.nrows; i++)
	{
		int k = 0;
		while (k < cub.ncols)
			printf("%3d ", cub.map[i][k++]);
		printf("|\n");
	}
	printf("ncol %d\n\n", cub.ncols);*/
	init_cam(&cub);
	init_mlx_func(&cub);
	mlx_hook(cub.libx.window, 2, 1, key_press_handler, &cub);
	mlx_hook(cub.libx.window, 3, 2, key_release_handler, &cub);
	mlx_hook(cub.libx.window, 17, (1U << 17), exit_handler, &cub);
	display_img(&cub);
	mlx_loop(cub.libx.mlx);
	return (0);
}
