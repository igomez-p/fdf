# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 15:29:03 by igomez-p          #+#    #+#              #
#    Updated: 2021/12/05 13:40:44 by igomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf.c				\
	  src/init.c		\
	  src/read_map.c	\
	  src/handler.c		\
	  src/window.c		\
	  library/ft_split.c \
	  library/get_next_line.c \
	  library/mem_functions.c	\
	  library/str_functions.c	\
	  library/number_functions.c\

LIB = minilibx-$(OS)/libmlx.a

OS  = $(shell uname -s)

OBJ = $(SRC:.c=.o)

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

clean:
		make -C minilibx-$(OS) clean
		rm -rf $(OBJ)

fclean: clean
		make -C minilibx-$(OS) clean
		rm -rf $(NAME)

re : fclean all
