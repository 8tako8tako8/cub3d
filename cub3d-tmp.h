/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:51:13 by kmorimot          #+#    #+#             */
/*   Updated: 2020/11/27 16:24:52 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx_mms_20200219/mlx.h"
# include "key_macos.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include "debug.h"
# include <fcntl.h>//open
# include <unistd.h>//read,close
# include <stdlib.h>//exit
# include <stdio.h>
# include <string.h>
# include <math.h>
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define TEX_WIDTH 64//テクスチャのテクセル(texel)の幅
# define TEX_HEIGHT 64//テクスチャのテクセル(texel)の高さ
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define WIDTH 640
# define HEIGHT 480
# define NUM_SPRITES 19

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				img_width;
	int				img_height;
}					t_img;

typedef struct		s_info
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	void			*mlx;
	void			*win;
	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	int				key_esc;
	int				buf[HEIGHT][WIDTH];
	double			zbuffer[WIDTH];
	int				**texture;
	double			movespeed;
	double			rotspeed;
}					t_info;

typedef struct		s_pair
{
	double			first;
	int				second;
}					t_pair;

typedef struct		s_floor
{
	float			raydirX0;
	float			raydirY0;
	float			raydirX1;
	float			raydirY1;
	int				p;
	float			posZ;
	float			rowdistance;
	float			floorstepX;
	float			floorstepY;
	float			floorX;
	float			floorY;
	int				cellX;
	int				cellY;
	int				tx;
	int				ty;
	int				floortexture;
	int				ceilingtexture;
	int				color;
	double			floorXwall;
	double			floorYwall;
	double			distwall;
	double			distplayer;
	double			currentdist;


/* 	double			weight;
	double			currentfloorX;
	double			currentfloorY;
	int				floortexX;
	int				floortexY;
	int				checkerboardpattern; */

}					t_floor;

typedef struct		s_ray
{
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
	double			wallX;
	double			olddirX;
	double			oldplaneX;

/* 	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				img_width;
	int				img_height;

	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	void			*mlx;
	void			*win;
	double			movespeed;
	double			rotspeed; */
	
//	int				color;

}					t_ray;

typedef struct		s_tex
{
	int				texnum;
	int				texX;
	double			step;
	double			texpos;
	int				texY;
	int				color;

/* 	int				**buf;
	int				buf[HEIGHT][WIDTH];
	int				texture[8][TEX_HEIGHT * TEX_WIDTH];
	int				**texture;
	int				xorcolor;
	int				ycolor;
	int				xycolor; */
}					t_tex;

/* typedef struct		s_cubflag
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;

}					t_cubflag; */

/* typedef struct		s_win
{
	int				x;
	int				y;
}					t_win; */

/* typedef struct		s_path_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_path_tex; */

/* typedef struct		s_ceiling
{
    int			    r;
    int			    g;
    int			    b;
}					t_ceiling; */

/* typedef struct		s_map_size
{
    int			    linelen;
    int			    numline;
}					t_map_size; */

/* typedef struct		s_map
{
    char            map[MAP_SIZE_Y][MAP_SIZE_X];
    //int             numline;
}					t_map; */

/* typedef struct		s_start_point
{
    char            dir;
    int             flag;
    int             x;
    int             y;
}					t_start_point; */

/* typedef struct		s_point
{
	int				x;
	int				y;
}					t_point; */


/* typedef struct		s_sprite
{
	double		x;
	double		y;
	int			texture;
}					t_sprite; */

typedef struct		s_all
{
	t_img			img;
	t_info			info;
	t_pair			pair;
	t_floor			floor;
	t_ray			ray;
	t_tex			tex;
}					t_all;

void	key_update(t_all *all);


void	ft_get_win(t_all *all, char **line);
void	ft_parse_line_r(t_all *all, char **line);
void	ft_read_map(t_all *all, int fd);
void	ft_init_all(t_all *all);

#endif