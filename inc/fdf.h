/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:51:44 by igomez-p          #+#    #+#             */
/*   Updated: 2021/12/04 20:24:10 by igomez-p         ###   ########.fr       */
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
# define MAX_NUM			50
# define SPACE				' '
# define EMPTY				'0'
# define WALL				'1'
# define OBJECT				'2'
# define NORTH				'N'
# define SOUTH				'S'
# define WEST				'W'
# define EAST				'E'
# define NO					1
# define SO					0
# define EA					3
# define WE					2
# define MAX_TEXTURES		4
# define MAX_LEN			10
# define TOTAL_IDS			8
# define TOTAL_INFO			9
# define VIEW_ANGLE			32.5
# define SQUARES_SEC		0.09
# define RADIANS_SEC		0.03
# define AND_ING			8355711
# define FRAME_TIME			1000.0
# define BYTE				256
# define BMP_HEADER_BYTES	54
# define DATA_INIT			54
# define BMP_HEADER_SIZE	40
# define NUM_PLANES			1
# define HORIZ_RESOLUTION	24
# define WID_TAM			600
# define HEI_TAM			700

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

/*typedef struct s_draw {
	int			start;
	int			end;
	double		wallx;
	double		wally;
	int			repaint;
}				t_draw;*/

typedef struct s_check {
	int			res;
	int			map;
}				t_check;

typedef struct s_read {
	char		*b;
	char		*l;
	//char		*stc;
	int			*stc;
	int			*sizes;
}				t_read;

typedef struct s_cub {
	int			nrows;
	int			ncols;
	char		*line;
//	char		**map;
	int			**map;
	t_render	res;
	t_minilix	libx;
	t_img		win;
	//t_draw		draw;
	t_check		check;
	t_read		r;
}				t_cub;

char			*info_map(char *line, char *stc, t_cub *cub);
void			init_struct(t_cub *info);
void			init_mlx_func(t_cub *c);
void			read_cub(char *filename, t_cub *info);
int				key_press_handler(int key, t_cub *c);
int				key_release_handler(int key, t_cub *c);
int				exit_handler(t_cub *c);
void			clean_exit(t_cub *c, char *str, int error);
int				paint_game(t_cub *c);
void			step_initial_side(t_cub *c);
int				move_keys(t_cub *c, double speed);
int				rotate_keys(t_cub *c, double speed);
void			free_map(t_cub *c);
//void			refill_map(t_cub *c);
int				draw(t_cub *c);
void			my_mlx_pixel_put(t_cub *c, int x, int y, int color);
void			check_extension(char *filename);
void			remove_spaces(t_cub *c, char **line);
void			check_map_wall(t_cub *c);
int				map_dimensions(t_cub *c);
//void			ft_split(char **s, char z, t_cub *c);
char			**ft_split(char const *s1, char c);
//int				ft_isspace(char c);
void			free_str_exit(t_cub *c, char *txt, char *str);
//int				is_char_valid(char c);
//int				empty_line(char *line);
int				check_bad_end(t_cub *c);
void			parse_map(char *filename, t_cub *map);

#endif
