/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:51:44 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/06 11:50:03 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# ifdef	MAC_SYSTEM
#  include "../minilibx-Darwin/mlx.h"
# elif	LINUX_SYSTEM
#  include "../minilibx-Linux/mlx.h"
# endif
# ifdef	MAC_SYSTEM
#  include "keycode_mac.h"
# elif	LINUX_SYSTEM
#  include "keycode_linux.h"
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "libft.h"
# define WID_TAM			1000
# define HEI_TAM			800
# define ZOOM				8
# define ANGLE				0.1
# define PERSPECTIVE_ANGLE	0.53
# define ISOMETRIC			1
# define PLANE				0
# define OBLIQUE			0
# define COLOR_1			0x00ffdc
# define COLOR_2			0xff6b38
# define COLOR_3			0xffffff
# define COLOR_4			0xe23030
# define COLOR_5			0x0083ff
# define COLOR_6			0xffec00

typedef struct s_render {
	int			x;
	int			y;
}				t_render;

typedef struct s_minilibx {
	void		*mlx;
	void		*window;
}				t_minilix;

typedef struct s_img {
	void		*img;
	int			*addr;
	int			hei;
	int			wid;
	int			sz;
	int			endian;
	int			bpp;
}				t_img;

typedef struct s_read {
	char		*b;
	char		*l;
	char		**buf;
}				t_read;

typedef struct s_cam {
	float		pangle;
	int			zoom;
	int			x;
	int			y;
	float		angle;
	int			isometric;
	int			oblique;
	int			plane;
	int			rotate[3];
}				t_cam;

typedef struct s_range {
	int			max;
	int			min;
	int			range;
}				t_range;

typedef struct s_point {
	int			x;
	int			y;
}				t_point;

typedef struct s_vbles {
	int			x;
	int			y;
	int			d;
	int			dy;
	int			dx;
	int			xi;
	int			yi;
}				t_vbles;

typedef struct s_cub {
	int			nrows;
	int			ncols;
	char		*line;
	int			**map;
	int			color;
	t_render	res;
	t_minilix	libx;
	t_img		win;
	t_cam		cam;
	t_range		r;
	t_read		read;
}				t_fdf;

void			init_struct(t_fdf *info);
void			init_mlx_func(t_fdf *c);
int				key_press_handler(int key, t_fdf *c);
int				key_release_handler(int key, t_fdf *c);
int				exit_handler(t_fdf *c);
void			clean_exit(t_fdf *c, char *str, int error);
void			free_map(t_fdf *c);
void			my_mlx_pixel_put(t_fdf *c, int x, int y, int color);
void			check_extension(char *filename);
void			ft_split(char const *s1, char c, t_fdf *d);
void			parse_map(char *filename, t_fdf *map);
void			plotline(t_point p0, int x1, int y1, t_fdf *data);
void			perform_zoom(t_point *p0, t_point *p1, int z[2], t_fdf *data);
void			perform_position(t_point *p0, t_point *p1, t_fdf *data);
void			init_cam(t_fdf *data);
int				display_img(t_fdf *d);

#endif
