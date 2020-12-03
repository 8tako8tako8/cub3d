/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_untex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:51:47 by kmorimot          #+#    #+#             */
/*   Updated: 2020/11/29 03:14:55 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d-old.h"
#include "minilibx_mms_20200219/mlx.h"
#include "key_macos.h"

int	worldmap[7][7] = {
										{1,1,1,1,1,1,1},
										{1,0,0,0,0,0,1},
										{1,0,8,0,0,0,1},
										{1,0,0,1,0,0,1},
										{1,0,0,0,0,0,1},
										{1,0,0,0,0,0,1},
										{1,1,1,1,1,1,1}
						};

void	verLine(t_all *all, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(all->ray.mlx, all->ray.win, x, y, color);
		y++;
	}
}

void	calc(t_all *all)
{
	int		x;

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
		all->ray.hit = 0; //壁に当たったか？初期化
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
			all->ray.perpwalldist = (all->ray.mapX - all->ray.posX + (1 - all->ray.stepX) / 2) / all->ray.raydirX;//カメラ平面から距離
		else
			all->ray.perpwalldist = (all->ray.mapY - all->ray.posY + (1 - all->ray.stepY) / 2) / all->ray.raydirY;//カメラ平面からの距離

		//Calculate height of line to draw on screen
		all->ray.lineheight = (int)(HEIGHT / all->ray.perpwalldist);

		//calculate lowest and highest pixel to fill in current stripe
		all->ray.drawstart = - all->ray.lineheight / 2 + HEIGHT / 2;
		if(all->ray.drawstart < 0)
			all->ray.drawstart = 0;//画面外は0
		all->ray.drawend = all->ray.lineheight / 2 + HEIGHT / 2;
		if(all->ray.drawend >= HEIGHT)
			all->ray.drawend = HEIGHT - 1;//画面外はHEIGHT-1

		if (worldmap[all->ray.mapY][all->ray.mapX] == 1)
			all->ray.color = 0xFF0000;
		else if (worldmap[all->ray.mapY][all->ray.mapX] == 2)
			all->ray.color = 0x00FF00;
		else if (worldmap[all->ray.mapY][all->ray.mapX] == 3)
			all->ray.color = 0x0000FF;
		else if (worldmap[all->ray.mapY][all->ray.mapX] == 4)
			all->ray.color = 0xFFFFFF;
		else
			all->ray.color = 0xFFFF00;
		
		if (all->ray.side == 1)
			all->ray.color = all->ray.color / 2;

		verLine(all, x, all->ray.drawstart, all->ray.drawend, all->ray.color);
		x++;
	}
}

int	main_loop(t_all *all)
{
	calc(all);
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

int	main(void)
{
	t_all	all;
	all.ray.mlx = mlx_init();

	all.ray.posX = 12;
	all.ray.posY = 5;
	all.ray.dirX = -1;
	all.ray.dirY = 0;
	all.ray.planeX = 0;
	all.ray.planeY = 0.66;
	all.ray.movespeed = 0.05;
	all.ray.rotspeed = 0.05;
	
	all.ray.win = mlx_new_window(all.ray.mlx, WIDTH, HEIGHT, "mlx");

	mlx_loop_hook(all.ray.mlx, &main_loop, &all);
	mlx_hook(all.ray.win, X_EVENT_KEY_PRESS, 0, &key_press, &all);

	mlx_loop(all.ray.mlx);
}
