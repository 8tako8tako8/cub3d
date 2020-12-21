# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/12 13:07:44 by kmorimot          #+#    #+#              #
#    Updated: 2020/12/20 13:34:20 by kmorimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
CC := gcc
CFLAGS :=
FLAGS := -lXext -lX11
MLX_DIR := ./minilibx-linux
LIBFT_DIR := ./libft
SRC_DIR := ./
SRCS := cub3d.c raycasting.c get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:.c=.o)
INCLUDE := -I.cub3d.h \
	   -I.get_next_line.h \
	   -I./libft/libft.h \
	   -I./minilibx-linux/mlx.h
AR := ar
ARFLAGS := rcs

all: $(NAME)

$(NAME):
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a .
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX_DIR)/libmlx_Linux.a .
	$(CC) $(CFLAGS) $(SRCS) libft.a libmlx_Linux.a $(FLAGS) -lm -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm ./libft.a
	$(MAKE) -C $(MLX_DIR) clean
	rm ./libmlx_Linux.a

re: fclean all

.PHONY: all clean fclean re
