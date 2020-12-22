/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:28:54 by yohlee            #+#    #+#             */
/*   Updated: 2020/12/21 21:45:50 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//---------------- utils ------------------------------

/* double  ft_decimals(double value)
{
    double  ret_decimals;

    ret_decimals = value - (int)value;
    return ret_decimals;
}

double  ft_floor(double value)
{
    double  ret_int;

    if (value < 0)
    {
        if (value < value - ft_decimals(value))
            ret_int = value - ft_decimals(value) - 1;
        else
            ret_int = (int)value;
    }
    else
        ret_int = (int)value;
    return (ret_int);
}

double	ft_absolute_value(double value)
{
	if (value < 0)
		value *= -1;
	return (value);
}

void		ft_free2(char **dst)
{
	int		i;

	i = 0;
	while (dst[i])
		i++;
	while (i > 0)
	{
		i--;
		if (dst[i])
			free(dst[i]);
	}
	if (dst)
		free(dst);
}

void		ft_free(int **dst)
{
	int		i;

	i = 0;
	while (dst[i])
		i++;
	while (i > 0)
	{
		i--;
		if (dst[i])
			free(dst[i]);
	}
	if (dst)
		free(dst);
}

int		ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
} */

//---------------- utils ------------------------------

//---------------- merge_sort ------------------------------

/* int			ft_cmp_distance_to_spr(t_sprlst *list1, t_sprlst *list2, double pos_x, double pos_y)
{
	double		distance1;
	double		distance2;

	distance1 = ((pos_x - list1->x) * (pos_x - list1->x) + (pos_y - list1->y) * (pos_y - list1->y));
	distance2 = ((pos_x - list2->x) * (pos_x - list2->x) + (pos_y - list2->y) * (pos_y - list2->y));
	if (distance1 >= distance2)
		return (1);
	else
		return (0);
}

t_sprlst	*ft_merge_lst(t_sprlst *list1, t_sprlst *list2, double pos_x, double pos_y)
{
    t_sprlst  *newlst_end;
    t_sprlst  newlst_head;

    newlst_end = &newlst_head;
    while ((list1 != NULL) && (list2 != NULL))
    {
        if (ft_cmp_distance_to_spr(list1, list2, pos_x, pos_y))
        {
            newlst_end->next = list1;
            list1 = list1->next;
            newlst_end = newlst_end->next;
        }
        else
        {
            newlst_end->next = list2;
            list2 = list2->next;
            newlst_end = newlst_end->next;
        }
    }
    if (list1 == NULL)
        newlst_end->next = list2;
    else
        newlst_end->next = list1;
    return (newlst_head.next);
}

t_sprlst  *ft_lst_merge_sort(t_sprlst *list, double pos_x, double pos_y)
{
    t_sprlst      *front;
    t_sprlst      *back;
    t_sprlst      *sepa;

    // 要素が１つ以下なら終了
    if (list == NULL || list->next == NULL)
        return (list);
    // リストの中心を探す。1:2でポインタを動かす。
    front = list;
    back = list->next;
	if (back != NULL)
		back = back->next;
    while (back != NULL)
    {
        front = front->next;
        back = back->next;
        if (back != NULL)
            back = back->next;
    }
    sepa = front->next;
    front->next = NULL;
    return (ft_merge_lst(ft_lst_merge_sort(list, pos_x, pos_y), ft_lst_merge_sort(sepa, pos_x, pos_y), pos_x, pos_y));
} */

//---------------- merge_sort ------------------------------

//------------------- event key ----------------------------------

/* int		ft_press_key(int key, t_all *all)
{
	if (key == K_ESC)
		ft_exit(all);
	else if (key == K_W)
		all->key.key_w = 1;
	else if (key == K_A)
		all->key.key_a = 1;
	else if (key == K_S)
		all->key.key_s = 1;
	else if (key == K_D)
		all->key.key_d = 1;
	else if (key == K_LEFT)
		all->key.key_left = 1;
	else if (key == K_RIGHT)
		all->key.key_right = 1;
	return (0);
}

int		 ft_release_key(int key, t_all *all)
{
	if (key == K_W)
		all->key.key_w = 0;
	else if (key == K_A)
		all->key.key_a = 0;
	else if (key == K_S)
		all->key.key_s = 0;
	else if (key == K_D)
		all->key.key_d = 0;
	else if (key == K_LEFT)
		all->key.key_left = 0;
	else if (key == K_RIGHT)
		all->key.key_right = 0;
	return (0);
} */

//------------------- event key ----------------------------------

//--------------- set pos ---------------------

/* void	ft_set_dir(t_all *all, double dirX, double dirY)
{
	all->player.dir_x = dirX;
	all->player.dir_y = dirY;
}

void	ft_set_plane(t_all *all, double planeX, double planeY)
{
	all->player.plane_x = planeX;
	all->player.plane_y = planeY;
}

void	ft_set_pos_and_dir_and_plane(t_all *all)
{
	all->player.pos_x = all->start_point.x;
	all->player.pos_y = all->start_point.y;
	if (all->start_point.dir == 'N')
	{
		ft_set_dir(all, 0.0, -1.0);
		ft_set_plane(all, 0.66, 0.0);
	}
	else if (all->start_point.dir == 'S')
	{
		ft_set_dir(all, 0.0, 1.0);
		ft_set_plane(all, -0.66, 0.0);
	}
	else if (all->start_point.dir == 'W')
	{
		ft_set_dir(all, -1.0, 0.0);
		ft_set_plane(all, 0.0, -0.66);
	}
	else if (all->start_point.dir == 'E')
	{
		ft_set_dir(all, 1.0, 0.0);
		ft_set_plane(all, 0.0, 0.66);
	}
} */

//--------------- set pos ---------------------

//------------------- floor casting --------------

/* void	ft_floor_casting(t_all *all)
{
	int		x;
	int		y;

	y = all->win_r.y / 2 + 1;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->win_r.buf[y][x] = all->color_f.rgb;
			all->win_r.buf[all->win_r.y - y - 1][x] = all->color_c.rgb;
			x++;
		}
		y++;
	}
} */

//------------------- floor casting --------------

//------------------- sprite casting --------------

/* void	ft_calc_sprite_tex(t_all *all)
{
	int		x;
	int		y;

	x = all->spr.draw_start_x;
	while (x < all->spr.draw_end_x)
	{
		all->spr.tex_x = (int)((256 * (x - (-all->spr.spr_width / 2 + all->spr.spr_screen_x)) * all->img.tex_width[4] / all->spr.spr_width) / 256);
		if (all->spr.transform_y > 0 && x > 0 && x < all->win_r.x && all->spr.transform_y < all->spr.zbuffer[x])
		{
			y = all->spr.draw_start_y;
			while (y < all->spr.draw_end_y)
			{
				all->spr.d = (y-all->spr.move_screen) * 256 - all->win_r.y * 128 + all->spr.spr_height * 128;
				all->spr.tex_y = ((all->spr.d * all->img.tex_height[4]) / all->spr.spr_height) / 256;
				all->spr.color = all->mlx.texture[4][all->img.tex_width[4] * all->spr.tex_y + all->spr.tex_x];
				if((all->spr.color & 0xFFFFFF) != 0)
					all->win_r.buf[y][x] = all->spr.color;
				y++;
			}
		}
		x++;
	}
}

void	ft_calc_sprite_drawing(t_all *all)
{
	// スクリーン上のスプライトの高さ
	all->spr.spr_height = (int)ft_absolute_value((all->win_r.y / all->spr.transform_y) / vDiv);
	//calculate lowest and highest pixel to fill in current stripe
	all->spr.draw_start_y = -all->spr.spr_height / 2 + all->win_r.y / 2 + all->spr.move_screen;
	if(all->spr.draw_start_y < 0)
		all->spr.draw_start_y = 0;
	all->spr.draw_end_y = all->spr.spr_height / 2 + all->win_r.y / 2 + all->spr.move_screen;
	if(all->spr.draw_end_y >= all->win_r.y)
		all->spr.draw_end_y = all->win_r.y - 1;
	// スプライトの幅を計算
	all->spr.spr_width = (int)ft_absolute_value((all->win_r.y / all->spr.transform_y) / uDiv);
	all->spr.draw_start_x = -all->spr.spr_width / 2 + all->spr.spr_screen_x;
	if(all->spr.draw_start_x < 0)
		all->spr.draw_start_x = 0;
	all->spr.draw_end_x = all->spr.spr_width / 2 + all->spr.spr_screen_x;
	if(all->spr.draw_end_x >= all->win_r.x)
		all->spr.draw_end_x = all->win_r.x - 1;
}

void	ft_set_elements_for_sprite_drawing(t_all *all, int *i)
{
	// カメラ平面に対するスプライトの位置
	all->spr.relative_x = all->spr.sprite_x[*i] - all->player.pos_x;
	all->spr.relative_y = all->spr.sprite_y[*i] - all->player.pos_y;
	all->spr.invdet = 1.0 / (all->player.plane_x * all->player.dir_y - all->player.dir_x * all->player.plane_y);
	all->spr.transform_x = all->spr.invdet * (all->player.dir_y * all->spr.relative_x - all->player.dir_x * all->spr.relative_y);
	all->spr.transform_y = all->spr.invdet * (-all->player.plane_y * all->spr.relative_x + all->player.plane_x * all->spr.relative_y);
	all->spr.spr_screen_x = (int)((all->win_r.x / 2) * (1 + all->spr.transform_x / all->spr.transform_y));
	all->spr.move_screen = (int)(vMove / all->spr.transform_y);
}

void	ft_store_lst_in_array(t_all *all)
{
	t_sprlst	*sprite;
	int			i;

	sprite = all->sprlst;
	i = 0;
	while (i < all->spr.num)
	{
		all->spr.sprite_x[i] = sprite->x;
		all->spr.sprite_y[i] = sprite->y;
		sprite = sprite->next;
		i++;
	}
}

void	ft_sprite_casting(t_all *all)
{
	int		i;
	
	//遠いスプライトから順に配列に格納
	all->sprlst = ft_lst_merge_sort(all->sprlst, all->player.pos_x, all->player.pos_y);
	ft_store_lst_in_array(all);
	i = 0;
	while (i < all->spr.num)
	{
		ft_set_elements_for_sprite_drawing(all, &i);
		ft_calc_sprite_drawing(all);
		ft_calc_sprite_tex(all);			
		i++;
	}
} */

//------------------- sprite casting --------------

//------------------- wall casting --------------

/* void	ft_calc_wall_tex(t_all *all, int *x)
{
	int		y;

	//テクスチャのx座標
	all->tex.tex_x = (int)(all->ray.wall_x * (double)(all->img.tex_width[all->tex.num]));
	if(all->ray.side == 0 && all->ray.raydir_x > 0)
		all->tex.tex_x = all->img.tex_width[all->tex.num] - all->tex.tex_x - 1;
	if(all->ray.side == 1 && all->ray.raydir_y < 0)
		all->tex.tex_x = all->img.tex_width[all->tex.num] - all->tex.tex_x - 1;
	all->tex.step = 1.0 * all->img.tex_height[all->tex.num] / all->ray.lineheight;
	all->tex.pos = (all->ray.drawstart - all->win_r.y / 2 + all->ray.lineheight / 2) * all->tex.step;
	y = all->ray.drawstart;
	while (y < all->ray.drawend)
	{
		all->tex.tex_y = ft_min((int)all->tex.pos, (all->img.tex_height[all->tex.num] - 1));
		all->tex.pos += all->tex.step;
		all->tex.color = all->mlx.texture[all->tex.num][(all->img.tex_height[all->tex.num]) * (all->tex.tex_y) + all->tex.tex_x];
		all->win_r.buf[y][*x] = all->tex.color;
		y++;
	}
}

void	ft_set_tex_for_each_direction(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydir_x < 0)
		all->tex.num = 0;
	else if (all->ray.side == 0 && all->ray.raydir_x >= 0)
		all->tex.num = 3;
	else if (all->ray.side == 1 && all->ray.raydir_y < 0)
		all->tex.num = 1;
	else if (all->ray.side == 1 && all->ray.raydir_y >= 0)
		all->tex.num = 2;
}

void	ft_calc_wall_drawing(t_all *all)
{
	all->ray.lineheight = (int)(all->win_r.y / all->ray.perpwalldist);//描画する壁の高さ
	all->ray.drawstart = -all->ray.lineheight / 2 + all->win_r.y / 2;
	if(all->ray.drawstart < 0)
		all->ray.drawstart = 0;//画面外は0
	all->ray.drawend = all->ray.lineheight / 2 + all->win_r.y / 2;
	if(all->ray.drawend >= all->win_r.y)
		all->ray.drawend = all->win_r.y - 1;//画面外はHEIGHT-1

	if (all->ray.side == 0)
		all->ray.wall_x = all->player.pos_y + all->ray.perpwalldist * all->ray.raydir_y;
	else
		all->ray.wall_x = all->player.pos_x + all->ray.perpwalldist * all->ray.raydir_x;
	all->ray.wall_x -= ft_floor(all->ray.wall_x);
}

void	ft_find_collision_with_wall(t_all *all)
{
	while (all->ray.hit == 0)
	{
		if(all->ray.sidedist_x < all->ray.sidedist_y)
		{
			all->ray.sidedist_x += all->ray.deltadist_x;
			all->ray.map_x += all->ray.step_x;
			all->ray.side = 0;//x面でヒットした時は0
		}
		else
		{
			all->ray.sidedist_y += all->ray.deltadist_y;
			all->ray.map_y += all->ray.step_y;
			all->ray.side = 1;//y面でヒットした時は1
		}
		if(all->map.map[all->ray.map_y][all->ray.map_x] == 1)//1のとき壁
			all->ray.hit = 1;
	}
	if(all->ray.side == 0)
		all->ray.perpwalldist = (all->ray.map_x - all->player.pos_x + (1 - all->ray.step_x) / 2) / all->ray.raydir_x;
	else
		all->ray.perpwalldist = (all->ray.map_y - all->player.pos_y + (1 - all->ray.step_y) / 2) / all->ray.raydir_y;
}

void	ft_set_step_and_sidedist(t_all *all)
{
	if(all->ray.raydir_x < 0)
	{
		all->ray.step_x = -1;
		all->ray.sidedist_x = (all->player.pos_x - all->ray.map_x) * all->ray.deltadist_x;
	}
	else
	{
		all->ray.step_x = 1;
		all->ray.sidedist_x = (all->ray.map_x + 1.0 - all->player.pos_x) * all->ray.deltadist_x;
	}
	if(all->ray.raydir_y < 0)
	{
		all->ray.step_y = -1;
		all->ray.sidedist_y = (all->player.pos_y - all->ray.map_y) * all->ray.deltadist_y;
	}
	else
	{
		all->ray.step_y = 1;
		all->ray.sidedist_y = (all->ray.map_y + 1.0 - all->player.pos_y) * all->ray.deltadist_y;
	}
}

void	ft_set_camera_and_raydir_and_deltadist(t_all *all, int x)
{
	all->ray.camera_x = 2 * x / (double)all->win_r.x - 1;//現在のx座標が表すカメラ平面上のx座標
	all->ray.raydir_x = all->player.dir_x + all->player.plane_x * all->ray.camera_x;//光線の方向ベクトル
	all->ray.raydir_y = all->player.dir_y + all->player.plane_y * all->ray.camera_x;//光線の方向ベクトル
	all->ray.map_x = (int)all->player.pos_x;//mapのどこにいるか
	all->ray.map_y = (int)all->player.pos_y;//mapのどこにいるか
	all->ray.deltadist_x = ft_absolute_value(1 / all->ray.raydir_x);
	all->ray.deltadist_y = ft_absolute_value(1 / all->ray.raydir_y);
}

void	ft_wall_casting(t_all *all)
{
	int		x;
	
	x = 0;
	while (x < all->win_r.x)
	{
		ft_set_camera_and_raydir_and_deltadist(all, x);
		all->ray.hit = 0;//壁に当たったか？初期化
		ft_set_step_and_sidedist(all);//stepとsidedistの初期値を求める。
		ft_find_collision_with_wall(all);//DDAアルゴリズムにより1マスずつ壁があるか見ていく
		ft_calc_wall_drawing(all);
		ft_set_tex_for_each_direction(all);
//		wallXは、壁の整数座標だけでなく、壁がヒットした正確な値を表す。
//		これは、使用する必要のあるテクスチャのx座標を知るために必要。
//		これは、最初に正確なx座標またはy座標を計算し、
//		次に壁の整数値を差し引くことによって計算される。
//		wallXと呼ばれていても、side==1の場合、実際には壁のy座標ですが、
//		常にテクスチャのx座標であることに注意する
		ft_calc_wall_tex(all, &x);
		all->spr.zbuffer[x] = all->ray.perpwalldist;
		x++;
	}
} */

//------------------- wall casting --------------

//----------------- move -------------------------

/* void	ft_turn_left(t_all *all)
{
	all->ray.olddir_x = all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(-all->player.rotspeed) - all->player.dir_y * sin(-all->player.rotspeed);
	all->player.dir_y = all->ray.olddir_x * sin(-all->player.rotspeed) + all->player.dir_y * cos(-all->player.rotspeed);
	all->ray.oldplane_x = all->player.plane_x;
	all->player.plane_x = all->player.plane_x * cos(-all->player.rotspeed) - all->player.plane_y * sin(-all->player.rotspeed);
	all->player.plane_y = all->ray.oldplane_x * sin(-all->player.rotspeed) + all->player.plane_y * cos(-all->player.rotspeed);
}

void	ft_turn_right(t_all *all)
{
	all->ray.olddir_x = all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(all->player.rotspeed) - all->player.dir_y * sin(all->player.rotspeed);
	all->player.dir_y = all->ray.olddir_x * sin(all->player.rotspeed) + all->player.dir_y * cos(all->player.rotspeed);
	all->ray.oldplane_x = all->player.plane_x;
	all->player.plane_x = all->player.plane_x * cos(all->player.rotspeed) - all->player.plane_y * sin(all->player.rotspeed);
	all->player.plane_y = all->ray.oldplane_x * sin(all->player.rotspeed) + all->player.plane_y * cos(all->player.rotspeed);
}

void	ft_move_forward(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x + all->player.dir_x * all->player.speed)])
		all->player.pos_x += all->player.dir_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y + all->player.dir_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y += all->player.dir_y * all->player.speed;
}

void	ft_move_backward(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x - all->player.dir_x * all->player.speed)])
		all->player.pos_x -= all->player.dir_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y - all->player.dir_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y -= all->player.dir_y * all->player.speed;
}

void	ft_move_left(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x - all->player.plane_x * all->player.speed)])
		all->player.pos_x -= all->player.plane_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y - all->player.plane_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y -= all->player.plane_y * all->player.speed;	
}

void	ft_move_right(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x + all->player.plane_x * all->player.speed)])
		all->player.pos_x += all->player.plane_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y + all->player.plane_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y += all->player.plane_y * all->player.speed;	
}

void	ft_move_player(t_all *all)
{
	if (all->key.key_w)
		ft_move_forward(all);
	if (all->key.key_s)
		ft_move_backward(all);
	if (all->key.key_a)
		ft_turn_left(all);
	if (all->key.key_d)
		ft_turn_right(all);
	if (all->key.key_right)
		ft_move_right(all);
	if (all->key.key_left)
		ft_move_left(all);
} */

//----------------- move -------------------------

//------------------- load ----------------------------------

/* void	ft_load_image(t_all *all, char *path)
{
	int			x;
	int			y;
	static int	i;

	if (!(all->img.img = mlx_xpm_file_to_image(all->mlx.mlx, path, &all->img.img_width, &all->img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	if (!(all->mlx.texture[i] = (int *)malloc(sizeof(int) * (all->img.img_height * all->img.img_width))))
		ft_put_error_and_exit("Cannot allocate memory\n", all);
	x = 0;
	while (x < all->img.img_height * all->img.img_width)
		all->mlx.texture[i][x++] = 0;
	y = 0;
	while (y < all->img.img_height)
	{
		x = 0;
		while (x < all->img.img_width)
		{
			all->mlx.texture[i][all->img.img_width * y + x] = all->img.data[all->img.size_l / 4 * y + x];
			x++;
		}
		y++;
	}
	all->img.tex_width[i] = all->img.img_width;
	all->img.tex_height[i] = all->img.img_height;
	i++;
	mlx_destroy_image(all->mlx.mlx, all->img.img);
}

void	ft_load_texture(t_all *all)
{
	ft_load_image(all, all->path_tex.west);
	ft_load_image(all, all->path_tex.north);
	ft_load_image(all, all->path_tex.south);
	ft_load_image(all, all->path_tex.east);
	ft_load_image(all, all->path_tex.sprite);
} */

//------------------- load tex ----------------------------------

//------------------- bmp ----------------------------------

/* void	ft_draw_window_save(t_all *all)
{
	int		x;
	int		y;

	y = 0;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->img.data[all->win_r.x * y + x] = all->win_r.buf[y][x];
			x++;
		}
		y++;
	}
}

void	ft_write_bmp_header(t_all *all, int fd, int filesize)
{
	unsigned char	fileheader[54];

	ft_bzero(fileheader, 54);
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(filesize);
	fileheader[3] = (unsigned char)(filesize >> 8);
	fileheader[4] = (unsigned char)(filesize >> 16);
	fileheader[5] = (unsigned char)(filesize >> 24);
	fileheader[10] = (unsigned char)(54);
	fileheader[14] = (unsigned char)(40);
	fileheader[18] = (unsigned char)(all->win_r.x);
	fileheader[19] = (unsigned char)(all->win_r.x >> 8);
	fileheader[20] = (unsigned char)(all->win_r.x >> 16);
	fileheader[21] = (unsigned char)(all->win_r.x >> 24);
	fileheader[22] = (unsigned char)((-1) * all->win_r.y);
	fileheader[23] = (unsigned char)((-1) * all->win_r.y >> 8);
	fileheader[24] = (unsigned char)((-1) * all->win_r.y >> 16);
	fileheader[25] = (unsigned char)((-1) * all->win_r.y >> 24);
	fileheader[26] = (unsigned char)(1);
	fileheader[28] = (unsigned char)(32);
	write(fd, fileheader, 54);
}

void	ft_save_bmp(t_all *all)
{
	int		filesize;
	int		fd;

	filesize = 54 + (4 * all->win_r.x * all->win_r.y);
	if ((fd = open("cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU)) < 0)
		ft_put_error_and_exit("Cannot create bmp\n", all);
	ft_write_bmp_header(all, fd, filesize);
	write(fd, (char *)all->img.data, 4 * all->win_r.x * all->win_r.y);
	close(fd);
}

void	ft_write_bmp(t_all *all)
{
	ft_floor_casting(all);
	ft_wall_casting(all);
	ft_sprite_casting(all);
	ft_draw_window_save(all);
	ft_save_bmp(all);
	ft_exit(all);
} */

//------------------- bmp ----------------------------------

//------------------- continue screen ----------------------------------

/* void	ft_draw_window(t_all *all)
{
	int		x;
	int		y;

	y = 0;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->img.data[all->img.size_l / 4 * y + x] = all->win_r.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->img.img, 0, 0);
}

int	ft_raycasting(t_all *all)
{
	ft_floor_casting(all);
	ft_wall_casting(all);
	ft_sprite_casting(all);
	ft_draw_window(all);
	ft_move_player(all);
	return (0);
} */

//------------------- continue screen ----------------------------------

//----------------- init mlx -------------------------

/* void	ft_init_buf_and_tex(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < all->win_r.y)
	{
		j = 0;
		while (j < all->win_r.x)
			all->win_r.buf[i][j++] = 0;
		i++;
	}
	if (!(all->mlx.texture = (int **)malloc(sizeof(int *) * 5)))
		ft_put_error_and_exit("Cannot allocate memory\n", all);
}

void	ft_init_buf_and_zbuffer(t_all *all)
{
	int			i;
	int			j;

	if (!(all->win_r.buf = (int **)malloc(sizeof(int *) * all->win_r.y)))
		ft_put_error_and_exit("Cannot allocate memory\n", all);
	i = 0;
	while (i < all->win_r.y)
		if (!(all->win_r.buf[i++] = (int *)malloc(sizeof(int) * all->win_r.x)))
			ft_put_error_and_exit("Cannot allocate memory\n", all);
	i = 0;
	while (i < all->win_r.y)
	{
		j = 0;
		while (j < all->win_r.x)
			all->win_r.buf[i][j++] = 0;
		i++;
	}
	if (!(all->spr.zbuffer =(double *)malloc(sizeof(double) * all->win_r.x)))
		ft_put_error_and_exit("Cannot allocate memory\n", all);
	j = 0;
	while (j < all->win_r.x)
		all->spr.zbuffer[j++] = 0;
}

void	ft_resize_win_size(t_all *all)
{
	if (all->win_r.x > all->win_r.screen_x)
		all->win_r.x = all->win_r.screen_x;
	if (all->win_r.y > all->win_r.screen_y)
		all->win_r.y = all->win_r.screen_y;
}

void	ft_init_mlx_and_win(t_all *all)
{
	if (!(all->mlx.mlx = mlx_init()))
		ft_put_error_and_exit("mlx_init failed\n", all);
	mlx_get_screen_size(all->mlx.mlx, &all->win_r.screen_x, &all->win_r.screen_y);
	ft_resize_win_size(all);
	ft_init_buf_and_zbuffer(all);
	ft_set_pos_and_dir_and_plane(all);
	ft_init_buf_and_tex(all);
	ft_load_texture(all);
	if (all->save == 0)
		if (!(all->mlx.win = mlx_new_window(all->mlx.mlx, all->win_r.x, all->win_r.y, "cub3d")))
			ft_put_error_and_exit("mlx_new_window failed\n", all);
	if (!(all->img.img = mlx_new_image(all->mlx.mlx, all->win_r.x, all->win_r.y)))
		ft_put_error_and_exit("mlx_new_image failed\n", all);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
} */

//----------------- init mlx -------------------------

//----------------- exit -------------------------

/* void	ft_put_error_and_exit(char *s, t_all *all)
{
	write(1, "\e[31mError\e[m\n", 15);
	ft_putstr_fd(s, 2);
	ft_exit(all);
}

void	ft_free_path(t_all *all)
{
	if (all->path_tex.north)
		free(all->path_tex.north);
	if (all->path_tex.south)
		free(all->path_tex.south);
	if (all->path_tex.west)
		free(all->path_tex.west);
	if (all->path_tex.east)
		free(all->path_tex.east);
	if (all->path_tex.sprite)
		free(all->path_tex.sprite);
}

int	ft_exit(t_all *all)
{
	if (all->img.img)
		mlx_destroy_image(all->mlx.mlx, all->img.img);
	if (all->mlx.mlx)
	{
		mlx_destroy_display(all->mlx.mlx);
		free(all->mlx.mlx);
	}
	ft_lstclear_ex(&(all->sprlst));
	ft_free(all->win_r.buf);
	ft_free(all->mlx.texture);
	if (all->spr.sprite_x)
		free(all->spr.sprite_x);
	if (all->spr.sprite_y)
		free(all->spr.sprite_y);
	if (all->spr.zbuffer)
		free(all->spr.zbuffer);
	ft_free_path(all);
	exit(0);
} */

//----------------- exit -------------------------
