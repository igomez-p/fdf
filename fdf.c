/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:52:45 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/07 06:19:39 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static void	check_argc(t_fdf *fdf, int n)
{
	if (n < 2 || n > 3)
		clean_exit(fdf, "Invalid number of arguments\n", 1);
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
	t_fdf	fdf;

	init_struct(&fdf);
	check_argc(&fdf, argc);
	check_extension(argv[1]);
	parse_map(argv[1], &fdf);
	init_cam(&fdf);
	init_mlx_func(&fdf);
	mlx_hook(fdf.libx.window, 2, 1, key_press_handler, &fdf);
	mlx_hook(fdf.libx.window, 3, 2, key_release_handler, &fdf);
	mlx_hook(fdf.libx.window, 17, (1U << 17), exit_handler, &fdf);
	display_img(&fdf);
	mlx_loop(fdf.libx.mlx);
	return (0);
}
