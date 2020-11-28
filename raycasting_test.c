/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:51:47 by kmorimot          #+#    #+#             */
/*   Updated: 2020/11/29 02:04:54 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d-old.h"
#include "minilibx_mms_20200219/mlx.h"
#include "key_macos.h"

int	worldmap[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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
		all->ray.color1 = 0xFF0000;
		all->ray.color2 = 0x00FF00;

		verLine(all, x, 0, HEIGHT/2, all->ray.color1);
		verLine(all, x, HEIGHT/2 + 1, HEIGHT, all->ray.color2);
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
