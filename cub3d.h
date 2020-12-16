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
# include <string.h>
# include <math.h>
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_WIDTH 50
# define MAP_HEIGHT 50
# define uDiv 1
# define vDiv 1
# define vMove 0.0

typedef struct		s_win_r
{
	int				x;
	int				y;
	int				screen_x;
	int				screen_y;
	int				**buf;
}					t_win_r;

typedef struct		s_path_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_path_tex;

typedef struct		s_color_f
{
    int			    r;
    int			    g;
    int			    b;
	int				rgb;
}					t_color_f;

typedef struct		s_color_c
{
    int			    r;
    int			    g;
    int			    b;
	int				rgb;
}					t_color_c;

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

typedef struct		s_map
{
    char	        charmap[MAP_HEIGHT][MAP_WIDTH];
    int	        	map[MAP_HEIGHT][MAP_WIDTH];
	int				start;
	int				end;
}					t_map;

typedef struct		s_start_point
{
    char            dir;
    int             flag;
    double          x;
    double          y;
}					t_start_point;

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				img_width;
	int				img_height;
	int				tex_width[5];
	int				tex_height[5];
}					t_img;

typedef struct		s_player
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			player_speed;
	double			player_rotspeed;
}					t_player;

typedef struct		s_info
{
	void			*mlx;
	void			*win;
	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	int				key_esc;
	int				**texture;

}					t_info;

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
	double			first;
	int				second;
}					t_pair;

typedef struct		s_sprlst
{
	double			x;
	double			y;
	struct s_sprlst	*next;
}					t_sprlst;

typedef struct		s_spr
{
	int				number;
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
	double			*zBuffer;
}					t_spr;

typedef struct		s_all
{
	int				save;
	t_win_r			win_r;
	t_path_tex		path_tex;
	t_color_f		color_f;
	t_color_c		color_c;
	t_cubflag		cubflag;
	t_map			map;
	t_start_point	start_point;

	t_img			img;
	t_player		player;
	t_info			info;
	t_ray			ray;
	t_tex			tex;
	t_pair			pair;
    t_spr           spr;
	t_sprlst		*sprlst;
}					t_all;

/* typedef struct		s_win_buf
{
	int				buf[all.win_r.y][all.win_r.x];
}					t_win_buf; */

void	key_update(t_all *all);
void	ft_raycasting(t_all *all);
void	ft_put_error_and_exit(char *s, int fd);
void	ft_write_bmp(t_all *all);
void	ft_put_success_or_error(char *s, int fd);

#endif