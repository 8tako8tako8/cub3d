# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/12 13:07:44 by kmorimot          #+#    #+#              #
#    Updated: 2020/12/28 12:07:59 by kmorimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
CC := gcc
#CFLAGS := -Wall -Wextra -Werror -g
CFLAGS := -g -fsanitize=address
LIBS := -lXext -lX11
MLX_DIR := ./minilibx-linux
LIBFT_DIR := ./libft
SRCS := srcs/bmp.c \
		srcs/exit.c \
		srcs/move.c \
		srcs/move2.c \
		srcs/continue_screen.c \
		srcs/flood_fill.c \
		srcs/init.c \
		srcs/parse_element.c \
		srcs/parse_element2.c \
		srcs/parse_element_content.c \
		srcs/sprite_casting.c \
		srcs/floor_casting.c \
		srcs/init_mlx.c \
		srcs/parse_map.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/libft_ex.c \
		srcs/libft_ex2.c \
		srcs/wall_casting.c \
		srcs/wall_casting2.c \
		srcs/load_tex.c \
		srcs/parse_line.c \
		srcs/event_key.c \
		srcs/merge_sort.c \
		srcs/set_position.c \
		srcs/cub3d.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c

OBJS := $(SRCS:.c=.o)
INCLUDE := -I.srcs
RM := rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX_DIR)/libmlx_Linux.a .
	$(CC) $(CFLAGS) $(OBJS) -L. -L.minilibx-linux -lmlx_Linux $(LIBS) -lm ./libft/libft.a -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) ./libmlx_Linux.a ./cub3d.bmp
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
