# include "minilibx_mms_20200219/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define numSprites 19
#define uDiv 1
#define vDiv 1
#define vMove 0.0

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

struct Sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	int		buf[height][width];
	double	zBuffer[width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;

    //floor
/* 	float			raydirX0;
	float			raydirY0;
	float			raydirX1;
	float			raydirY1;
	int				p1;
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
	int				color1;//1
	double			floorXwall;
	double			floorYwall;
	double			distwall;
	double			distplayer;
	double			currentdist; */

    //ray
/* 	double			cameraX;
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
	double			oldplaneX; */

    // tex
/* 	int				texnum;
	int				texX;
	double			step;
	double			texpos;
	int				texY;
	int				color2; */
}				t_info;

typedef struct		s_floor
{
	float			raydirX0;
	float			raydirY0;
	float			raydirX1;
	float			raydirY1;
	int				p;//1
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
	int				color1;//1
	int				color2;//1
	double			floorXwall;
	double			floorYwall;
	double			distwall;
	double			distplayer;
	double			currentdist;
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

}					t_ray;

typedef struct		s_tex
{
	int				texnum;
	int				texX1;//1
	double			step;
	double			texpos;
	int				texY1;//1
	int				color2;//2
}					t_tex;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

typedef struct		s_spr
{
    double          spriteX;
    double          spriteY;
    double          invDet;
	double          transformX;
	double          transformY;
	int             spriteScreenX;
    int             vMoveScreen;
    int             spriteHeight;
    int             spriteWidth;
    int             drawStartX;
    int             drawStartY;
    int             drawEndX;
    int             drawEndY;
    int             texX;
    int             texY;
    int             d;
    int             color3;

}					t_spr;

typedef struct		s_all
{
	t_img			img;
	t_info			info;
	t_floor			floor;
	t_ray			ray;
	t_tex			tex;
	t_pair			pair;
    t_spr           spr;
}					t_all;

void	key_update(t_all *all);