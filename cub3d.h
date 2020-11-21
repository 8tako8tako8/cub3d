/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:51:13 by kmorimot          #+#    #+#             */
/*   Updated: 2020/11/21 15:04:46 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "minilibx_mms_20200219/mlx.h"
#include "key_macos.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include "debug.h"
# include <fcntl.h>//open
# include <unistd.h>//read,close
# include <stdlib.h>//exit
# include <stdio.h>
#include <string.h>
#include <math.h>
# define MAP_SIZE_X 40
# define MAP_SIZE_Y 20

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define WIDTH 1920
#define HEIGHT 1080

typedef struct		s_cubflag
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
}					t_cubflag;

typedef struct		s_win
{
	int				x;
	int				y;
}					t_win;

typedef struct		s_path_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_path_tex;

typedef struct		s_floor
{
    int			    r;
    int			    g;
    int			    b;
}					t_floor;

typedef struct		s_ceiling
{
    int			    r;
    int			    g;
    int			    b;
}					t_ceiling;

/* typedef struct		s_map_size
{
    int			    linelen;
    int			    numline;
}					t_map_size; */

typedef struct		s_map
{
    char            map[MAP_SIZE_Y][MAP_SIZE_X];
    //int             numline;
}					t_map;

typedef struct		s_start_point
{
    char            dir;
    int             flag;
    int             x;
    int             y;
}					t_start_point;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_ray
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;

	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	void			*mlx;
	void			*win;
	double			movespeed;
	double			rotspeed;
	
	double			cameraX;
	double			raydirX;
	double			raydirY;
	int				mapX;
	int				mapY;
	double			sidedistX;
	double			sidedistY;
	double			deltadistX;
	double			deltadistY;
	double			perpwalldist;
	int				stepX;
	int				stepY;
	int				hit;
	int				side;

	int				lineheight;
	int				drawstart;
	int				drawend;
	int				color;

	double			olddirX;
	double			oldplaneX;
	
}					t_ray;

typedef struct		s_tex
{
	int				**buf;
	int				texture[8][TEX_HEIGHT * TEX_WIDTH];
	int				texnum;
	double			wallX;
	int				texX;
	int				texY;
	double			step;
	double			texpos;
	int				xorcolor;
	int				ycolor;
	int				xycolor;
}					t_tex;

typedef struct		s_all
{
	t_cubflag       cubflag;
	t_win           win;
	t_path_tex      path_tex;
	t_floor		    floor;
	t_ceiling		ceiling;
 //   t_map_size      map_size;
    t_map           map;
    t_start_point   start_point;
    t_point         point;
	t_ray			ray;
	t_tex			tex;
}					t_all;

void	ft_get_win(t_all *all, char **line);
void	ft_parse_line_r(t_all *all, char **line);
void	ft_read_map(t_all *all, int fd);
void	ft_init_all(t_all *all);

#endif