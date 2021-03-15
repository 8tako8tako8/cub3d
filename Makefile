# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/12 13:07:44 by kmorimot          #+#    #+#              #
#    Updated: 2021/03/16 02:21:24 by kmorimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
NAME	:=	cub3D
UNAME	:=	$(shell uname)
SRC_DIR	:=	./srcs
FT_DIR	:=	$(SRC_DIR)/libft
FT_LIB	:=	ft

ifeq	($(UNAME), Darwin)
MLX_DIR :=	$(SRC_DIR)/minilibx_mms_20200219
MLX_LIB :=	libmlx.dylib
LIBS    :=  -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L$(FT_DIR) -l$(FT_LIB)
else
ifeq	($(UNAME), Linux)
MLX_DIR :=	$(SRC_DIR)/minilibx-linux
MLX_LIB :=	libmlx_Linux.a
LIBS    :=	-L. -lmlx_Linux -lXext -lX11 -lm -L$(FT_DIR) -l$(FT_LIB)
endif
endif

SRCS := $(SRC_DIR)/bmp.c \
		$(SRC_DIR)/exit.c \
		$(SRC_DIR)/move.c \
		$(SRC_DIR)/move2.c \
		$(SRC_DIR)/continue_screen.c \
		$(SRC_DIR)/flood_fill.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/parse_element.c \
		$(SRC_DIR)/parse_element2.c \
		$(SRC_DIR)/parse_element_content.c \
		$(SRC_DIR)/sprite_casting.c \
		$(SRC_DIR)/floor_casting.c \
		$(SRC_DIR)/init_mlx.c \
		$(SRC_DIR)/parse_map.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/utils2.c \
		$(SRC_DIR)/libft_ex.c \
		$(SRC_DIR)/libft_ex2.c \
		$(SRC_DIR)/wall_casting.c \
		$(SRC_DIR)/wall_casting2.c \
		$(SRC_DIR)/load_tex.c \
		$(SRC_DIR)/parse_line.c \
		$(SRC_DIR)/event_key.c \
		$(SRC_DIR)/merge_sort.c \
		$(SRC_DIR)/set_position.c \
		$(SRC_DIR)/cub3d.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/get_next_line_utils.c

INCLUDE :=  -I$(FT_DIR) -I$(MLX_DIR) -I./includes
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) bonus -C $(FT_DIR)
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX_DIR)/$(MLX_LIB) .
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDE) $(SRCS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(FT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) $(MLX_LIB) ./cub3d.bmp 
	$(MAKE) -C $(FT_DIR) fclean

re: fclean all

.PHONY:	all clean fclean re bonus