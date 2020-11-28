/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_image_tex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:51:47 by kmorimot          #+#    #+#             */
/*   Updated: 2020/11/26 16:19:09 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx_mms_20200219/mlx.h"
#include "key_macos.h"

int	worldmap[MAP_WIDTH][MAP_HEIGHT] =
						{
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
							{1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,1,1,1},
							{1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
							{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
							{1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
							{1,0,0,0,0,0,0,1,1,1,1,0,2,1,1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,4,4,4,4,4,0,0,1,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,1,1,0,1,1},
							{1,0,1,0,1,0,0,0,0,3,0,1,0,1,0,0,1,0,0,0,0,0,0,1},
							{1,0,0,1,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,1,1,0,1,1},
							{1,0,1,0,1,0,0,0,0,3,0,0,0,1,0,0,1,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1}
						};

void	draw(t_all *all)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			all->ray.data[y * WIDTH + x] = all->tex.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->ray.mlx, all->ray.win, all->ray.img, 0, 0);
}

void	calc(t_all *all)
{
	int		x;
	int		y;

	x = 0;
	while (x < WIDTH)
	{
		all->ray.cameraX = 2 * x / (double)WIDTH - 1;//現在のx座標が表すカメラ平面上のx座標
		all->ray.raydirX = all->ray.dirX + all->ray.planeX * all->ray.cameraX;//光線の方向ベクトル
		all->ray.raydirY = all->ray.dirY + all->ray.planeY * all->ray.cameraX;//光線の方向ベクトル
		
		all->ray.mapX = (int)all->ray.posX;//mapのどこにいるか
		all->ray.mapY = (int)all->ray.posY;//mapのどこにいるか
		
		 //length of ray from one x or y-side to next x or y-side
		all->ray.deltadistX = fabs(1 / all->ray.raydirX);
		all->ray.deltadistY = fabs(1 / all->ray.raydirY);
		
		all->ray.hit = 0;//壁に当たったか？初期化
		//stepとsidedistの初期値を求める。
		if (all->ray.raydirX < 0)//raydirX<0の時stepX=-1,sidedistX=(mapX+1.0-posX)*deltadistX
		{
			all->ray.stepX = -1;
			all->ray.sidedistX = (all->ray.posX - all->ray.mapX) * all->ray.deltadistX;
		}
		else
		{
			all->ray.stepX = 1;
			all->ray.sidedistX = (all->ray.mapX + 1.0 - all->ray.posX) * all->ray.deltadistX;
		}
		if (all->ray.raydirY < 0)
		{
			all->ray.stepY = -1;
			all->ray.sidedistY = (all->ray.posY - all->ray.mapY) * all->ray.deltadistY;
		}
		else
		{
			all->ray.stepY = 1;
			all->ray.sidedistY = (all->ray.mapY + 1.0 - all->ray.posY) * all->ray.deltadistY;
		}

		while (all->ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			//DDAアルゴリズムにより1マスずつ壁があるか見ていく
			if (all->ray.sidedistX < all->ray.sidedistY)
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
			//Check if ray has hit a wall
			if (worldmap[all->ray.mapX][all->ray.mapY] > 0)//0より大きいと壁
				all->ray.hit = 1;//壁に当たったフラグ
		}
		if (all->ray.side == 0)
			all->ray.perpwalldist = (all->ray.mapX - all->ray.posX + (1 - all->ray.stepX) / 2) / all->ray.raydirX;
		else
			all->ray.perpwalldist = (all->ray.mapY - all->ray.posY + (1 - all->ray.stepY) / 2) / all->ray.raydirY;

		//Calculate height of line to draw on screen
		all->ray.lineheight = (int)(HEIGHT / all->ray.perpwalldist);

		//calculate lowest and highest pixel to fill in current stripe
		all->ray.drawstart = - all->ray.lineheight / 2 + HEIGHT / 2;
		if (all->ray.drawstart < 0)
			all->ray.drawstart = 0;//画面外は0
		all->ray.drawend = all->ray.lineheight / 2 + HEIGHT / 2;
		if (all->ray.drawend >= HEIGHT)
			all->ray.drawend = HEIGHT - 1;//画面外はHEIGHT-1

		// texturing calculations
		//選択されたテクスチャの種類を表す変数texNumはマップで光線がぶつかった壁のマス値から1を減算入手することができる。
		//テクスチャ0が存在するが、マップタイル0は空のスペースを表すため、テクスチャがないから。
		//worldmap[mapX][mapY]の値が1の場合texnumが0になって、テクスチャの種類の中で一番最初のテクスチャを使用できるようになる。
		all->tex.texnum = worldmap[all->ray.mapX][all->ray.mapY];
		
		//wallXは、壁の整数座標だけでなく、壁がヒットした正確な値を表す。
		//これは、使用する必要のあるテクスチャのx座標を知るために必要。
		//これは、最初に正確なx座標またはy座標を計算し、
		//次に壁の整数値を差し引くことによって計算される。
		//wallXと呼ばれていても、side==1の場合、実際には壁のy座標ですが、
		//常にテクスチャのx座標であることに注意する。
		if (all->ray.side == 0)
			all->tex.wallX = all->ray.posY + all->ray.perpwalldist * all->ray.raydirY;
		else
			all->tex.wallX = all->ray.posX + all->ray.perpwalldist * all->ray.raydirX;
		all->tex.wallX = all->tex.wallX - (int)all->tex.wallX;

		//テクスチャのx座標
		all->tex.texX = (int)(all->tex.wallX * (double)TEX_WIDTH);
		if (all->ray.side == 0 && all->ray.raydirX > 0)
			all->tex.texX = TEX_WIDTH - all->tex.texX - 1;
		if (all->ray.side == 1 && all->ray.raydirY < 0)
			all->tex.texX = TEX_WIDTH - all->tex.texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		all->tex.step = 1.0 * TEX_HEIGHT / all->ray.lineheight;
		// Starting texture coordinate
		all->tex.texpos = (all->ray.drawstart - HEIGHT / 2 + all->ray.lineheight / 2) * all->tex.step;
		y = all->ray.drawstart;
		while (y < all->ray.drawend)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			all->tex.texY = (int)all->tex.texpos & (TEX_HEIGHT - 1);
			all->tex.texpos += all->tex.step;
			all->ray.color = all->tex.texture[all->tex.texnum][TEX_HEIGHT * all->tex.texY + all->tex.texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (all->ray.side == 1)
				all->ray.color = (all->ray.color >> 1) & 8355711;
			all->tex.buf[y][x] = all->ray.color;
			y++;
		}
		x++;
	}
}

int	main_loop(t_all *all)
{
	calc(all);
	draw(all);
	// mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);
	return (0);
}

int	key_press(int key, t_all *all)
{
	if (key == K_W)
	{
		if (!worldmap[(int)(all->ray.posX + all->ray.dirX * all->ray.movespeed)][(int)(all->ray.posY)])
			all->ray.posX += all->ray.dirX * all->ray.movespeed;
		if (!worldmap[(int)(all->ray.posX)][(int)(all->ray.posY + all->ray.dirY * all->ray.movespeed)])
			all->ray.posY += all->ray.dirY * all->ray.movespeed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldmap[(int)(all->ray.posX - all->ray.dirX * all->ray.movespeed)][(int)(all->ray.posY)])
			all->ray.posX -= all->ray.dirX * all->ray.movespeed;
		if (!worldmap[(int)(all->ray.posX)][(int)(all->ray.posY - all->ray.dirY * all->ray.movespeed)])
			all->ray.posY -= all->ray.dirY * all->ray.movespeed;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		all->ray.olddirX = all->ray.dirX;
		all->ray.dirX = all->ray.dirX * cos(-all->ray.rotspeed) - all->ray.dirY * sin(-all->ray.rotspeed);
		all->ray.dirY = all->ray.olddirX * sin(-all->ray.rotspeed) + all->ray.dirY * cos(-all->ray.rotspeed);
		all->ray.oldplaneX = all->ray.planeX;
		all->ray.planeX = all->ray.planeX * cos(-all->ray.rotspeed) - all->ray.planeY * sin(-all->ray.rotspeed);
		all->ray.planeY = all->ray.oldplaneX * sin(-all->ray.rotspeed) + all->ray.planeY * cos(-all->ray.rotspeed);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		all->ray.olddirX = all->ray.dirX;
		all->ray.dirX = all->ray.dirX * cos(all->ray.rotspeed) - all->ray.dirY * sin(all->ray.rotspeed);
		all->ray.dirY = all->ray.olddirX * sin(all->ray.rotspeed) + all->ray.dirY * cos(all->ray.rotspeed);
		all->ray.oldplaneX = all->ray.planeX;
		all->ray.planeX = all->ray.planeX * cos(all->ray.rotspeed) - all->ray.planeY * sin(all->ray.rotspeed);
		all->ray.planeY = all->ray.oldplaneX * sin(all->ray.rotspeed) + all->ray.planeY * cos(all->ray.rotspeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}

void	load_image(t_all *all, int *texture, char *path)
{
	int		x;
	int		y;

	all->ray.img = mlx_xpm_file_to_image(all->ray.mlx, path, &all->ray.img_width, &all->ray.img_height);
	all->ray.data = (int *)mlx_get_data_addr(all->ray.img, &all->ray.bpp, &all->ray.size_l, &all->ray.endian);
	
	y = 0;
	while (y < all->ray.img_height)
	{
		x = 0;
		while (x < all->ray.img_width)
		{
			texture[all->ray.img_width * y + x] = all->ray.data[all->ray.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(all->ray.mlx, all->ray.img);
}

void	load_texture(t_all *all)
{
	load_image(all, all->tex.texture[0], "textures/eagle.xpm");
	load_image(all, all->tex.texture[1], "textures/redbrick.xpm");
	load_image(all, all->tex.texture[2], "textures/purplestone.xpm");
	load_image(all, all->tex.texture[3], "textures/greystone.xpm");
	load_image(all, all->tex.texture[4], "textures/bluestone.xpm");
	load_image(all, all->tex.texture[5], "textures/mossy.xpm");
	load_image(all, all->tex.texture[6], "textures/wood.xpm");
	load_image(all, all->tex.texture[7], "textures/colorstone.xpm");
}

int	main(void)
{
	t_all	all;
	int		i;
	int		j;
	int		x;
	int		y;

	all.ray.mlx = mlx_init();
	all.ray.posX = 22.0;
	all.ray.posY = 11.5;
	all.ray.dirX = -1.0;
	all.ray.dirY = 0.0;
	all.ray.planeX = 0.0;
	all.ray.planeY = 0.66;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			all.tex.buf[i][j++] = 0;
		i++;
	}
	if (!(all.tex.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	i = 0;
	while (i < 8)
	{
		if (!(all.tex.texture[i] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH))))
			return (-1);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
			all.tex.texture[i][j++] = 0;
		i++;
	}

	load_texture(&all);

	all.ray.movespeed = 0.05;
	all.ray.rotspeed = 0.05;
	
	all.ray.win = mlx_new_window(all.ray.mlx, WIDTH, HEIGHT, "mlx");

	all.ray.img = mlx_new_image(all.ray.mlx, WIDTH, HEIGHT);
	all.ray.data = (int *)mlx_get_data_addr(all.ray.img, &all.ray.bpp, &all.ray.size_l, &all.ray.endian);

	mlx_loop_hook(all.ray.mlx, &main_loop, &all);
	mlx_hook(all.ray.win, X_EVENT_KEY_PRESS, 0, &key_press, &all);

	mlx_loop(all.ray.mlx);
}