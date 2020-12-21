/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1217.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:28:54 by yohlee            #+#    #+#             */
/*   Updated: 2020/12/21 01:34:36 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_cmp_distance_to_spr(t_sprlst *list1, t_sprlst *list2, double posX, double posY)
{
	double		distance1;
	double		distance2;

	distance1 = ((posX - list1->x) * (posX - list1->x) + (posY - list1->y) * (posY - list1->y));
	distance2 = ((posX - list2->x) * (posX - list2->x) + (posY - list2->y) * (posY - list2->y));
	if (distance1 >= distance2)
		return (1);
	else
		return (0);
}

t_sprlst	*ft_merge_lst(t_sprlst *list1, t_sprlst *list2, double posX, double posY)
{
    t_sprlst  *newlst_end;
    t_sprlst  newlst_head;

    newlst_end = &newlst_head;
    while ((list1 != NULL) && (list2 != NULL))
    {
        if (ft_cmp_distance_to_spr(list1, list2, posX, posY))
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

t_sprlst  *ft_lst_merge_sort(t_sprlst *list, double posX, double posY)
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
    return (ft_merge_lst(ft_lst_merge_sort(list, posX, posY), ft_lst_merge_sort(sepa, posX, posY), posX, posY));
}

double  ft_decimals(double value)
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

void	ft_draw_window(t_all *all)
{
	int		x;
	int		y;

	y = 0;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->img.data[all->img.size_l / (all->img.bpp / 8) * y + x] = all->win_r.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->info.mlx, all->info.win, all->img.img, 0, 0);
}

void	ft_draw_window_save(t_all *all)
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
	mlx_put_image_to_window(all->info.mlx, all->info.win, all->img.img, 0, 0);
}

void	ft_floor_casting(t_all *all)
{
	int		x;
	int		y;

	y = all->win_r.y / 2 + 1;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			// floor
			//all->floor.color = all->color_f.rgb;
			all->win_r.buf[y][x] = all->color_f.rgb;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			//all->floor.color = all->color_c.rgb;
			all->win_r.buf[all->win_r.y - y - 1][x] = all->color_c.rgb;
			x++;
		}
		y++;
	}
}

void	ft_set_camera_and_raydir_and_deltadist(t_all *all, int x)
{
	//calculate ray position and direction
	all->ray.cameraX = 2 * x / (double)all->win_r.x - 1;//現在のx座標が表すカメラ平面上のx座標
	all->ray.raydirX = all->player.dirX + all->player.planeX * all->ray.cameraX;//光線の方向ベクトル
	all->ray.raydirY = all->player.dirY + all->player.planeY * all->ray.cameraX;//光線の方向ベクトル
	//which box of the map we're in
	all->ray.mapX = (int)all->player.posX;//mapのどこにいるか
	all->ray.mapY = (int)all->player.posY;//mapのどこにいるか

	all->ray.deltadistX = ft_absolute_value(1 / all->ray.raydirX);
	all->ray.deltadistY = ft_absolute_value(1 / all->ray.raydirY);
}

void	ft_set_step_and_sidedist(t_all *all)
{
	if(all->ray.raydirX < 0)
	{
		all->ray.stepX = -1;
		all->ray.sidedistX = (all->player.posX - all->ray.mapX) * all->ray.deltadistX;
	}
	else
	{
		all->ray.stepX = 1;
		all->ray.sidedistX = (all->ray.mapX + 1.0 - all->player.posX) * all->ray.deltadistX;
	}
	if(all->ray.raydirY < 0)
	{
		all->ray.stepY = -1;
		all->ray.sidedistY = (all->player.posY - all->ray.mapY) * all->ray.deltadistY;
	}
	else
	{
		all->ray.stepY = 1;
		all->ray.sidedistY = (all->ray.mapY + 1.0 - all->player.posY) * all->ray.deltadistY;
	}
}

void	ft_find_collision_with_wall(t_all *all)
{
	while (all->ray.hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if(all->ray.sidedistX < all->ray.sidedistY)
		{
			all->ray.sidedistX += all->ray.deltadistX;
			all->ray.mapX += all->ray.stepX;
			all->ray.side = 0;//x面でヒットした時は0
		}
		else
		{
			all->ray.sidedistY += all->ray.deltadistY;
			all->ray.mapY += all->ray.stepY;
			all->ray.side = 1;//y面でヒットした時は1
		}
		if(all->map.map[all->ray.mapY][all->ray.mapX] == 1)//1のとき壁
			all->ray.hit = 1;
	}
	if(all->ray.side == 0)
		all->ray.perpwalldist = (all->ray.mapX - all->player.posX + (1 - all->ray.stepX) / 2) / all->ray.raydirX;
	else
		all->ray.perpwalldist = (all->ray.mapY - all->player.posY + (1 - all->ray.stepY) / 2) / all->ray.raydirY;
}

void	ft_calc_wall_drawing(t_all *all)
{
	all->ray.lineheight = (int)(all->win_r.y / all->ray.perpwalldist);//描画する壁の高さ
	//calculate lowest and highest pixel to fill in current stripe
	all->ray.drawstart = -all->ray.lineheight / 2 + all->win_r.y / 2;
	if(all->ray.drawstart < 0)
		all->ray.drawstart = 0;//画面外は0
	all->ray.drawend = all->ray.lineheight / 2 + all->win_r.y / 2;
	if(all->ray.drawend >= all->win_r.y)
		all->ray.drawend = all->win_r.y - 1;//画面外はHEIGHT-1
}

void	ft_set_tex_for_each_direction(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydirX < 0)
		all->tex.texnum = 0; //1 subtracted from it so that texture 0 can be used!
	else if (all->ray.side == 0 && all->ray.raydirX >= 0)
		all->tex.texnum = 3;
	else if (all->ray.side == 1 && all->ray.raydirY < 0)
		all->tex.texnum = 1;
	else if (all->ray.side == 1 && all->ray.raydirY >= 0)
		all->tex.texnum = 2;
}

void	ft_calc_raycasting(t_all *all)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		stripe;

	//FLOOR CASTING
	ft_floor_casting(all);

	// WALL CASTING
//	ft_wall_casting(all);
	x = 0;
	while (x < all->win_r.x)
	{
		ft_set_camera_and_raydir_and_deltadist(all, x);
		all->ray.hit = 0;//壁に当たったか？初期化
		ft_set_step_and_sidedist(all);//stepとsidedistの初期値を求める。
		ft_find_collision_with_wall(all);//DDAアルゴリズムにより1マスずつ壁があるか見ていく
		ft_calc_wall_drawing(all);
		ft_set_tex_for_each_direction(all);
		/* wallXは、壁の整数座標だけでなく、壁がヒットした正確な値を表す。
		これは、使用する必要のあるテクスチャのx座標を知るために必要。
		これは、最初に正確なx座標またはy座標を計算し、
		次に壁の整数値を差し引くことによって計算される。
		wallXと呼ばれていても、side==1の場合、実際には壁のy座標ですが、
		常にテクスチャのx座標であることに注意する。 */
		if (all->ray.side == 0)
			all->ray.wallX = all->player.posY + all->ray.perpwalldist * all->ray.raydirY;
		else
			all->ray.wallX = all->player.posX + all->ray.perpwalldist * all->ray.raydirX;
		all->ray.wallX -= ft_floor(all->ray.wallX);
		//テクスチャのx座標
		all->tex.texX1 = (int)(all->ray.wallX * (double)(all->img.tex_width[all->tex.texnum]));
		if(all->ray.side == 0 && all->ray.raydirX > 0)
			all->tex.texX1 = all->img.tex_width[all->tex.texnum] - all->tex.texX1 - 1;
		if(all->ray.side == 1 && all->ray.raydirY < 0)
			all->tex.texX1 = all->img.tex_width[all->tex.texnum] - all->tex.texX1 - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		all->tex.step = 1.0 * all->img.tex_height[all->tex.texnum] / all->ray.lineheight;
		// Starting texture coordinate
		all->tex.texpos = (all->ray.drawstart - all->win_r.y / 2 + all->ray.lineheight / 2) * all->tex.step;
		y = all->ray.drawstart;
		while (y < all->ray.drawend)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			//all->tex.texY1 = (int)all->tex.texpos & (all->img.tex_height[all->tex.texnum] - 1);
			all->tex.texY1 = (int)all->tex.texpos;
			all->tex.texpos += all->tex.step;
			all->tex.color2 = all->info.texture[all->tex.texnum][(all->img.tex_height[all->tex.texnum]) * (all->tex.texY1) + all->tex.texX1];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
/* 			if(all->ray.side == 1)
				all->tex.color2 = (all->tex.color2 >> 1) & 8355711; */
			all->win_r.buf[y][x] = all->tex.color2;
			y++;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		all->spr.zBuffer[x] = all->ray.perpwalldist; //perpendicular distance is used
		x++;
	}
//	ft_sprite_casting();
	//遠いスプライトから順に配列に格納
	all->sprlst = ft_lst_merge_sort(all->sprlst, all->player.posX, all->player.posY);
	double		sprite_x[all->spr.number];
	double		sprite_y[all->spr.number];
	t_sprlst *sprite;

	sprite = all->sprlst;
	i = 0;
	while (i < all->spr.number)
	{
		sprite_x[i] = sprite->x;
		sprite_y[i] = sprite->y;
		sprite = sprite->next;
		i++;
	}
	i = 0;
	while (i < all->spr.number)
	{
//		ft_set_sprite_
//		ft_calc_sprite_drawing();
		// カメラ平面に対するスプライトの位置
		all->spr.spriteX = sprite_x[i] - all->player.posX;
		all->spr.spriteY = sprite_y[i] - all->player.posY;

		all->spr.invDet = 1.0 / (all->player.planeX * all->player.dirY - all->player.dirX * all->player.planeY); //required for correct matrix multiplication

		all->spr.transformX = all->spr.invDet * (all->player.dirY * all->spr.spriteX - all->player.dirX * all->spr.spriteY);
		all->spr.transformY = all->spr.invDet * (-all->player.planeY * all->spr.spriteX + all->player.planeX * all->spr.spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		all->spr.spriteScreenX = (int)((all->win_r.x / 2) * (1 + all->spr.transformX / all->spr.transformY));

		all->spr.vMoveScreen = (int)(vMove / all->spr.transformY);

		// スクリーン上のスプライトの高さ
		all->spr.spriteHeight = (int)ft_absolute_value((all->win_r.y / all->spr.transformY) / vDiv);

		//calculate lowest and highest pixel to fill in current stripe
		all->spr.drawStartY = -all->spr.spriteHeight / 2 + all->win_r.y / 2 + all->spr.vMoveScreen;
		if(all->spr.drawStartY < 0)
			all->spr.drawStartY = 0;
		all->spr.drawEndY = all->spr.spriteHeight / 2 + all->win_r.y / 2 + all->spr.vMoveScreen;
		if(all->spr.drawEndY >= all->win_r.y)
			all->spr.drawEndY = all->win_r.y - 1;

		// スプライトの幅を計算
		all->spr.spriteWidth = (int)ft_absolute_value((all->win_r.y / all->spr.transformY) / uDiv);
		
		all->spr.drawStartX = -all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
		if(all->spr.drawStartX < 0)
			all->spr.drawStartX = 0;
		all->spr.drawEndX = all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
		if(all->spr.drawEndX >= all->win_r.x)
			all->spr.drawEndX = all->win_r.x - 1;

		stripe = all->spr.drawStartX;
		while (stripe < all->spr.drawEndX)
		{
			all->spr.texX = (int)((256 * (stripe - (-all->spr.spriteWidth / 2 + all->spr.spriteScreenX)) * all->img.tex_width[4] / all->spr.spriteWidth) / 256);
			if (all->spr.transformY > 0 && stripe > 0 && stripe < all->win_r.x && all->spr.transformY < all->spr.zBuffer[stripe])
			{
				y = all->spr.drawStartY;
				while (y < all->spr.drawEndY) //for every pixel of the current stripe
				{
					all->spr.d = (y-all->spr.vMoveScreen) * 256 - all->win_r.y * 128 + all->spr.spriteHeight * 128; //256 and 128 factors to avoid floats
					all->spr.texY = ((all->spr.d * all->img.tex_height[4]) / all->spr.spriteHeight) / 256;
					all->spr.color3 = all->info.texture[4][all->img.tex_width[4] * all->spr.texY + all->spr.texX]; //get current color from the texture
					if((all->spr.color3 & 0xFFFFFF) != 0) all->win_r.buf[y][stripe] = all->spr.color3; //paint pixel if it isn't black, black is the invisible color
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

void	ft_update_key(t_all *all)
{
	if (all->info.key_w)
	{
		if (!all->map.map[(int)(all->player.posY)][(int)(all->player.posX + all->player.dirX * all->player.player_speed)])
			all->player.posX += all->player.dirX * all->player.player_speed;
		if (!all->map.map[(int)(all->player.posY + all->player.dirY * all->player.player_speed)][(int)(all->player.posX)])
			all->player.posY += all->player.dirY * all->player.player_speed;
	}
	if (all->info.key_s)
	{
		if (!all->map.map[(int)(all->player.posY)][(int)(all->player.posX - all->player.dirX * all->player.player_speed)])
			all->player.posX -= all->player.dirX * all->player.player_speed;
		if (!all->map.map[(int)(all->player.posY - all->player.dirY * all->player.player_speed)][(int)(all->player.posX)])
			all->player.posY -= all->player.dirY * all->player.player_speed;
	}
	if (all->info.key_a)
	{
		all->ray.olddirX = all->player.dirX;
		all->player.dirX = all->player.dirX * cos(-all->player.player_rotspeed) - all->player.dirY * sin(-all->player.player_rotspeed);
		all->player.dirY = all->ray.olddirX * sin(-all->player.player_rotspeed) + all->player.dirY * cos(-all->player.player_rotspeed);
		all->ray.oldplaneX = all->player.planeX;
		all->player.planeX = all->player.planeX * cos(-all->player.player_rotspeed) - all->player.planeY * sin(-all->player.player_rotspeed);
		all->player.planeY = all->ray.oldplaneX * sin(-all->player.player_rotspeed) + all->player.planeY * cos(-all->player.player_rotspeed);
	}
	if (all->info.key_d)
	{
		all->ray.olddirX = all->player.dirX;
		all->player.dirX = all->player.dirX * cos(all->player.player_rotspeed) - all->player.dirY * sin(all->player.player_rotspeed);
		all->player.dirY = all->ray.olddirX * sin(all->player.player_rotspeed) + all->player.dirY * cos(all->player.player_rotspeed);
		all->ray.oldplaneX = all->player.planeX;
		all->player.planeX = all->player.planeX * cos(all->player.player_rotspeed) - all->player.planeY * sin(all->player.player_rotspeed);
		all->player.planeY = all->ray.oldplaneX * sin(all->player.player_rotspeed) + all->player.planeY * cos(all->player.player_rotspeed);
	}
	if (all->info.key_esc)
		exit(0);
}

static void		ft_free1(int **dst, int i)
{
	while (i > 0)
	{
		i--;
		free(dst[i]);
	}
	free(dst);
}

int		ft_press_key(int key, t_all *all)
{
	if (key == K_ESC)
	{
		write(1, "1", 1);
		ft_lstclear_ex(&(all->sprlst));
		ft_free1(all->win_r.buf, all->win_r.y);
		ft_free1(all->info.texture, 5);
		free(all->spr.zBuffer);
		free(all->path_tex.north);
		free(all->path_tex.south);
		free(all->path_tex.west);
		free(all->path_tex.east);
		free(all->path_tex.sprite);
		mlx_destroy_image(all->info.mlx, all->img.img);
		system("leaks a.out");
		exit(0);
	}
	else if (key == K_W)
		all->info.key_w = 1;
	else if (key == K_A)
		all->info.key_a = 1;
	else if (key == K_S)
		all->info.key_s = 1;
	else if (key == K_D)
		all->info.key_d = 1;
	return (0);
}

int		 ft_release_key(int key, t_all *all)
{
	if (key == K_ESC)
	{
		exit(0);
	}
	else if (key == K_W)
		all->info.key_w = 0;
	else if (key == K_A)
		all->info.key_a = 0;
	else if (key == K_S)
		all->info.key_s = 0;
	else if (key == K_D)
		all->info.key_d = 0;
	return (0);
}

int		ft_destroy_win(int key, t_all *all)
{
/* 	ft_lstclear_ex(&(all->sprlst));
	ft_free1(all->win_r.buf, all->win_r.y);
	ft_free1(all->info.texture, 5);
	free(all->spr.zBuffer); */
/* 	free(all->path_tex.north);
	free(all->path_tex.south);
	free(all->path_tex.west);
	free(all->path_tex.east);
	free(all->path_tex.sprite); */
	system("leaks a.out");
	exit(0);
}

void	ft_load_image(t_all *all, char *path)
{
	int			x;
	int			y;
	static int	i;

	if (!(all->img.img = mlx_xpm_file_to_image(all->info.mlx, path, &all->img.img_width, &all->img.img_height)))
		ft_put_error_and_exit("Invalid path\n", 2);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", 2);
	if (!(all->info.texture[i] = (int *)malloc(sizeof(int) * (all->img.img_height * all->img.img_width))))
		ft_put_error_and_exit("Cannot allocate memory\n", 2);
	x = 0;
	while (x < all->img.img_height * all->img.img_width)
		all->info.texture[i][x++] = 0;
	y = 0;
	while (y < all->img.img_height)
	{
		x = 0;
		while (x < all->img.img_width)
		{
			all->info.texture[i][all->img.img_width * y + x] = all->img.data[all->img.img_width * y + x];
			x++;
		}
		y++;
	}
	all->img.tex_width[i] = all->img.img_width;
	all->img.tex_height[i] = all->img.img_height;
	i++;
	mlx_destroy_image(all->info.mlx, all->img.img);
}

void	ft_load_texture(t_all *all)
{
	ft_load_image(all, all->path_tex.west);
	ft_load_image(all, all->path_tex.north);
	ft_load_image(all, all->path_tex.south);
	ft_load_image(all, all->path_tex.east);
	ft_load_image(all, all->path_tex.sprite);
}

void	ft_set_dir(t_all *all, double dirX, double dirY)
{
	all->player.dirX = dirX;
	all->player.dirY = dirY;
}

void	ft_set_plane(t_all *all, double planeX, double planeY)
{
	all->player.planeX = planeX;
	all->player.planeY = planeY;
}

void	ft_set_pos_and_dir_and_plane(t_all *all)
{
	all->player.posX = all->start_point.x;
	all->player.posY = all->start_point.y;
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
}

void	ft_init_buf_and_tex(t_all *all)
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
	if (!(all->info.texture = (int **)malloc(sizeof(int *) * 5)))
		ft_put_error_and_exit("Cannot allocate memory\n", 2);
}

int	main_loop(t_all *all)
{
	ft_calc_raycasting(all);
	ft_draw_window(all);
	ft_update_key(all);
	return (0);
}

void	ft_resize_win_size(t_all *all)
{
	if (all->win_r.x > all->win_r.screen_x)
		all->win_r.x = all->win_r.screen_x;
	if (all->win_r.y > all->win_r.screen_y)
		all->win_r.y = all->win_r.screen_y;
}

void	ft_init_buf_and_zbuffer(t_all *all)
{
	int			i;
	int			j;

	if (!(all->win_r.buf = (int **)malloc(sizeof(int *) * all->win_r.y)))
		ft_put_error_and_exit("Cannot allocate memory\n", 2);
	i = 0;
	while (i < all->win_r.y)
		if (!(all->win_r.buf[i++] = (int *)malloc(sizeof(int) * all->win_r.x)))
			ft_put_error_and_exit("Cannot allocate memory\n", 2);
	i = 0;
	while (i < all->win_r.y)
	{
		j = 0;
		while (j < all->win_r.x)
			all->win_r.buf[i][j++] = 0;
		i++;
	}
	if (!(all->spr.zBuffer =(double *)malloc(sizeof(double) * all->win_r.x)))
		ft_put_error_and_exit("Cannot allocate memory\n", 2);
	j = 0;
	while (j < all->win_r.x)
		all->spr.zBuffer[j++] = 0;
}

void	ft_raycasting(t_all *all)
{
	if (!(all->info.mlx = mlx_init()))
		ft_put_error_and_exit("mlx_init failed\n", 2);
	mlx_get_screen_size(all->info.mlx, &all->win_r.screen_x, &all->win_r.screen_y);
	ft_resize_win_size(all);
	ft_init_buf_and_zbuffer(all);
	
	ft_set_pos_and_dir_and_plane(all);
	ft_init_buf_and_tex(all);
	ft_load_texture(all);
	if (!(all->info.win = mlx_new_window(all->info.mlx, all->win_r.x, all->win_r.y, "cub3d")))
		ft_put_error_and_exit("mlx_new_window failed\n", 2);
	if (!(all->img.img = mlx_new_image(all->info.mlx, all->win_r.x, all->win_r.y)))
		ft_put_error_and_exit("mlx_new_image failed\n", 2);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", 2);
	ft_put_success_or_error("Start drawing\n", 1);//Success
	mlx_loop_hook(all->info.mlx, &main_loop, all);
	mlx_hook(all->info.win, KEY_PRESS, 0, &ft_press_key, all);
	mlx_hook(all->info.win, KEY_RELEASE, 0, &ft_release_key, all);
	mlx_hook(all->info.win, DESTROY_NOTIFY, 1L<<17, &ft_destroy_win, all);
	mlx_loop(all->info.mlx);
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
		ft_put_error_and_exit("Cannot create bmp\n", 2);
	ft_write_bmp_header(all, fd, filesize);
	write(fd, (char *)all->img.data, 4 * all->win_r.x * all->win_r.y);
	close(fd);
	exit(0);
}

void	ft_write_bmp(t_all *all)
{
//	if (!(all->info.mlx = mlx_init()))
//		ft_put_error_and_exit("mlx_init failed\n", 2);
	mlx_get_screen_size(all->info.mlx, &all->win_r.screen_x, &all->win_r.screen_y);
	ft_resize_win_size(all);
	ft_init_buf_and_zbuffer(all);
	ft_set_pos_and_dir_and_plane(all);
	ft_init_buf_and_tex(all);
	ft_load_texture(all);
	if (!(all->info.win = mlx_new_window(all->info.mlx, all->win_r.x, all->win_r.y, "cub3d")))
		ft_put_error_and_exit("mlx_new_window failed\n", 2);
	if (!(all->img.img = mlx_new_image(all->info.mlx, all->win_r.x, all->win_r.y)))
		ft_put_error_and_exit("mlx_new_image failed\n", 2);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", 2);
	ft_calc_raycasting(all);
	ft_draw_window_save(all);
	ft_save_bmp(all);
}