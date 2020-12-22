/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:23:21 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 22:29:30 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "key_linux.h"
# include "get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# define MAP_WIDTH 50
# define MAP_HEIGHT 50

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
	int				r;
	int				g;
	int				b;
	int				rgb;
}					t_color_f;

typedef struct		s_color_c
{
	int				r;
	int				g;
	int				b;
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
	int				mlx_start;
}					t_cubflag;

typedef struct		s_map
{
	char			charmap[MAP_HEIGHT][MAP_WIDTH];
	int				map[MAP_HEIGHT][MAP_WIDTH];
	int				start;
	int				end;
}					t_map;

typedef struct		s_start_point
{
	char			dir;
	int				flag;
	double			x;
	double			y;
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
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			speed;
	double			rotspeed;
}					t_player;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	int				**texture;
}					t_mlx;

typedef struct		s_key
{
	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	int				key_left;
	int				key_right;
	int				key_esc;
}					t_key;

typedef struct		s_ray
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			perpwalldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wall_x;
	double			olddir_x;
	double			oldplane_x;
}					t_ray;

typedef struct		s_tex
{
	int				num;
	int				tex_x;
	int				tex_y;
	double			step;
	double			pos;
	int				color;
}					t_tex;

typedef struct		s_sprlst
{
	double			x;
	double			y;
	struct s_sprlst	*next;
}					t_sprlst;

typedef struct		s_spr
{
	int				num;
	double			*sprite_x;
	double			*sprite_y;
	double			relative_x;
	double			relative_y;
	double			*zbuffer;
	double			invdet;
	double			transform_x;
	double			transform_y;
	int				spr_screen_x;
	int				spr_height;
	int				spr_width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
	int				d;
	int				color;
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
	t_mlx			mlx;
	t_key			key;
	t_ray			ray;
	t_tex			tex;
	t_spr			spr;
	t_sprlst		*sprlst;
}					t_all;

double				ft_decimals(double value);
double				ft_floor(double value);
double				ft_absolute_value(double value);
void				ft_free(int **dst, int i);
void				ft_free2(char **dst);
int					ft_min(int x, int y);
int					ft_cmp_distance_to_spr(t_sprlst *list1, t_sprlst *list2,
	double pos_x, double pos_y);
t_sprlst			*ft_merge_lst(t_sprlst *list1, t_sprlst *list2,
	double pos_x, double pos_y);
t_sprlst			*ft_lst_merge_sort(t_sprlst *list,
	double pos_x, double pos_y);
int					ft_press_key(int key, t_all *all);
int					ft_release_key(int key, t_all *all);
void				ft_set_dir(t_all *all, double dir_x, double dir_y);
void				ft_set_plane(t_all *all, double plane_x, double plane_y);
void				ft_set_pos_and_dir_and_plane(t_all *all);
void				ft_floor_casting(t_all *all);
void				ft_calc_sprite_tex(t_all *all);
void				ft_calc_sprite_tex2(t_all *all, int *x);
void				ft_calc_sprite_drawing(t_all *all);
void				ft_set_elements_for_sprite_drawing(t_all *all, int *i);
void				ft_sprite_casting(t_all *all);
void				ft_calc_wall_tex(t_all *all, int *x);
void				ft_set_tex_for_each_direction(t_all *all);
void				ft_calc_wall_drawing(t_all *all);
void				ft_find_collision_with_wall(t_all *all);
void				ft_set_step_and_sidedist(t_all *all);
void				ft_set_camera_and_raydir_and_deltadist(t_all *all, int x);
void				ft_wall_casting(t_all *all);
void				ft_turn_left(t_all *all);
void				ft_turn_right(t_all *all);
void				ft_move_forward(t_all *all);
void				ft_move_backward(t_all *all);
void				ft_move_left(t_all *all);
void				ft_move_right(t_all *all);
void				ft_move_player(t_all *all);
void				ft_load_image(t_all *all, char *path);
void				ft_load_image2(t_all *all, int i);
void				ft_load_texture(t_all *all);
void				ft_draw_window_save(t_all *all);
void				ft_write_bmp_header(t_all *all, int fd, int filesize);
void				ft_save_bmp(t_all *all);
void				ft_write_bmp(t_all *all);
void				ft_draw_window(t_all *all);
int					ft_raycasting(t_all *all);
void				ft_init_buf_and_tex(t_all *all);
void				ft_init_buf_and_zbuffer(t_all *all);
void				ft_resize_win_size(t_all *all);
void				ft_init_mlx_and_win(t_all *all);
void				ft_free_path(t_all *all);
int					ft_exit(t_all *all);
void				ft_put_error_and_exit(char *s, t_all *all);
int					ft_isspace(char c);
int					ft_isonlyspace(char **line);
void				ft_combine_color(t_all *all);
int					ft_atoi_ex(const char *str);
int					ft_strchr_ex(char *s, char c);
void				ft_lstclear_ex(t_sprlst **lst);
t_sprlst			*ft_newspr(double x, double y);
t_sprlst			*ft_lstlast_ex(t_sprlst *lst);
void				ft_lstadd_back_ex(t_sprlst **lst, t_sprlst *new);
int					ft_lstsize_ex(t_sprlst *lst);
void				ft_convert_map_char_to_int(t_all *all);
void				ft_flood_fill_recursion(t_all *all, int x, int y);
void				ft_flood_fill(t_all *all);
void				ft_get_win(t_all *all, char **line);
void				ft_skip_digit(char **line, int *i, int *count);
void				ft_get_floor(t_all *all, char **line);
void				ft_get_ceiling(t_all *all, char **line);
char				*ft_get_path(char **line, t_all *all);
void				ft_parse_line_r(t_all *all, char **line);
void				ft_parse_line_no(t_all *all, char **line);
void				ft_parse_line_so(t_all *all, char **line);
void				ft_parse_line_we(t_all *all, char **line);
void				ft_parse_line_ea(t_all *all, char **line);
void				ft_parse_line_s(t_all *all, char **line);
void				ft_parse_line_f(t_all *all, char **line);
void				ft_parse_line_c(t_all *all, char **line);
void				ft_set_start_point(t_all *all, char **line, int *i, int *j);
void				ft_parse_map(t_all *all, char **line);
int					ft_ismap(t_all *all, char *line);
int					ft_check_after_map(char *line);
void				ft_check_element_and_parse_map(t_all *all, char **line);
void				ft_parse_line(t_all *all, char **line);
void				ft_read_cub(t_all *all, int fd);
void				ft_init_sprite(t_all *all);
void				ft_init_all(t_all *all, int argc);
void				ft_init_key_and_path(t_all *all);
void				ft_init_map(t_all *all);
void				ft_init(t_all *all, int argc);
int					ft_iscub(char *cub);

#endif
