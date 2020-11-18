#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>//open
# include <unistd.h>//read,close
# include <stdlib.h>//exit
# include <stdio.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "debug.h"
# define MAP_SIZE_X 40
# define MAP_SIZE_Y 20

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

typedef struct		s_posi
{
    char            dir;
    int             posiflag;
    int             posix;
    int             posiy;
}					t_posi;

typedef struct		s_all
{
	t_cubflag       cubflag;
	t_win           win;
	t_path_tex      path_tex;
	t_floor		    floor;
	t_ceiling		ceiling;
 //   t_map_size      map_size;
    t_map           map;
    t_posi          posi;
}					t_all;

void	ft_get_win(t_all *all, char **line);
void	ft_parse_line_r(t_all *all, char **line);
void	ft_read_map(t_all *all, int fd);
void	ft_init_all(t_all *all);

#endif