# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igomez-p <igomez-p@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 15:29:03 by igomez-p          #+#    #+#              #
#    Updated: 2021/12/06 13:02:27 by igomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf.c				\
	  src/init.c		\
	  src/read_map.c	\
	  src/handler.c		\
	  src/image.c		\
	  src/bresenham.c	\
	  src/camera.c		\
	  library/ft_split.c \
	  library/get_next_line.c \
	  library/mem_functions.c	\
	  library/str_functions.c	\
	  library/number_functions.c\

SRC_BONUS = fdf.c					\
			src_bonus/init_bonus.c		\
			src_bonus/read_map_bonus.c	\
			src_bonus/handler_bonus.c		\
			src_bonus/image_bonus.c		\
			src_bonus/bresenham_bonus.c	\
			src_bonus/camera_bonus.c		\
			src_bonus/movement_bonus.c	\
			library/ft_split.c \
			library/get_next_line.c \
			library/mem_functions.c	\
			library/str_functions.c	\
			library/number_functions.c\

LIB = minilibx-$(OS)/libmlx.a

OS  = $(shell uname -s)

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

ifeq ($(OS), Darwin)
    MINILIB = -framework OpenGL -framework AppKit
else
    MINILIB = -lm -lz -lXext -lX11 -L ./minilibx-Linux -pthread
endif

ifeq ($(OS), Darwin)
    SYSTEM = -D MAC_SYSTEM=1
else
    SYSTEM = -D LINUX_SYSTEM=1
endif

%.o: %.c
	gcc $(SYSTEM) -Wall -Werror -Wextra -g -I /usr/local/include -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C minilibx-$(OS)/
		gcc -Wall -Werror -Wextra -g $(OBJ) -I /usr/local/include $(LIB) $(MINILIB) -o $(NAME)

bonus: $(OBJ_BONUS)
		$(MAKE) -C minilibx-$(OS)/
		gcc -Wall -Werror -Wextra -g $(OBJ_BONUS) -I /usr/local/include $(LIB) $(MINILIB) -o $(NAME)

clean:
		make -C minilibx-$(OS) clean
		rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
		make -C minilibx-$(OS) clean
		rm -rf $(NAME)

re : fclean all
