# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/12 13:07:44 by kmorimot          #+#    #+#              #
#    Updated: 2020/12/20 00:20:20 by kmorimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
CC := gcc
CFLAGS := -Wall -Wextra -Werror -framework OpenGL -framework AppKit
FLAGS := -framework OpenGL -framework AppKit
MLX_DIR := ./minilibx_mms_20200219
MLX_LIB := libmlx.dylib
SRC_DIR := ./
SRCS := cub3d.c raycasting.c get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:.c=.o)
INCLUDE := -I.cub3d.h \
	   -I./libft/libft.h \
	   -I./minilibx_mms_20200219/mlx.h

AR := ar
ARFLAGS := rcs

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

all: $(NAME)

$(NAME):  $(OBJS) $(MLX_LIB)
	$(MAKE) -C ./libft
	cp libft/libft.a .
	$(MAKE) -C ./minilibx_mms_20200219
	cp ./minilibx_mms_20200219/libmlx.dylib .
	$(CC) -o $(NAME) $(CFLAGS) $(SRCS) libft.a libmlx.dylib $(FLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean
	rm ./libft.a

re: fclean all

.PHONY: all clean fclean re
