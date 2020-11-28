/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:28:54 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 01:56:46 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	compare(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
		return (1);
	else if (*(int *)first < *(int *)second)
		return (-1);
	else
		return (0);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

int	worldMap[mapWidth][mapHeight] =
									{
										{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
										{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
										{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
										{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
										{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
										{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
										{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
									};

void	draw(t_all *all)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			all->img.data[y * width + x] = all->info.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->info.mlx, all->info.win, all->img.img, 0, 0);
}

void	verLine(t_all *all, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(all->info.mlx, all->info.win, x, y, color);
		y++;
	}
}

void	calc(t_all *all)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		stripe;

	x = 0;
	while (x < width)
	{
		all->floor.color1 = 0xFF0000;


		verLine(all, x, 0, height/2, all->floor.color1);
		verLine(all, x, height/2 + 1, height, all->floor.color2);
		x++;
	}
/* 	//FLOOR CASTING
	y = height / 2 + 1;
	while (y < height)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		all->floor.raydirX0 = all->info.dirX - all->info.planeX;
		all->floor.raydirY0 = all->info.dirY - all->info.planeY;
		all->floor.raydirX1 = all->info.dirX + all->info.planeX;
		all->floor.raydirY1 = all->info.dirY + all->info.planeY;
		// Current y position compared to the center of the screen (the horizon)
		all->floor.p = y - height / 2;
		// Vertical position of the camera.
		all->floor.posZ = 0.5 * height;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		all->floor.rowdistance = all->floor.posZ / all->floor.p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		all->floor.floorstepX = all->floor.rowdistance * (all->floor.raydirX1 - all->floor.raydirX0) / width;
		all->floor.floorstepY = all->floor.rowdistance * (all->floor.raydirY1 - all->floor.raydirY0) / width;
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		all->floor.floorX = all->info.posX + all->floor.rowdistance * all->floor.raydirX0;
		all->floor.floorY = all->info.posY + all->floor.rowdistance * all->floor.raydirY0;
		x = 0;
		while (x < width)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			all->floor.cellX = (int)(all->floor.floorX);
			all->floor.cellY = (int)(all->floor.floorY);
			// get the texture coordinate from the fractional part
			all->floor.tx = (int)(texWidth * (all->floor.floorX - all->floor.cellX)) & (texWidth - 1);
			all->floor.ty = (int)(texHeight * (all->floor.floorY - all->floor.cellY)) & (texHeight - 1);
			all->floor.floorX += all->floor.floorstepX;
			all->floor.floorY += all->floor.floorstepY;

			all->floor.floortexture = 3;
			all->floor.ceilingtexture = 6;

			// floor
			all->floor.color1 = all->info.texture[all->floor.floortexture][texWidth * all->floor.ty + all->floor.tx];
			all->floor.color1 = (all->floor.color1 >> 1) & 8355711; // make a bit darker
			all->info.buf[y][x] = all->floor.color1;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			all->floor.color1 = all->info.texture[all->floor.ceilingtexture][texWidth * all->floor.ty + all->floor.tx];
			all->floor.color1 = (all->floor.color1 >> 1) & 8355711; // make a bit darker
			all->info.buf[height - y - 1][x] = all->floor.color1;
			x++;
		}
		y++;
	} */
	// WALL CASTING
	for(int x = 0; x < width; x++)
	{
		//calculate ray position and direction
		all->ray.cameraX = 2 * x / (double)width - 1; //x-coordinate in camera space
		all->ray.raydirX = all->info.dirX + all->info.planeX * all->ray.cameraX;
		all->ray.raydirY = all->info.dirY + all->info.planeY * all->ray.cameraX;
		//which box of the map we're in
		all->ray.mapX = (int)all->info.posX;
		all->ray.mapY = (int)all->info.posY;

		//length of ray from one x or y-side to next x or y-side
		all->ray.deltadistX = fabs(1 / all->ray.raydirX);
		all->ray.deltadistY = fabs(1 / all->ray.raydirY);

		all->ray.hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if(all->ray.raydirX < 0)
		{
			all->ray.stepX = -1;
			all->ray.sidedistX = (all->info.posX - all->ray.mapX) * all->ray.deltadistX;
		}
		else
		{
			all->ray.stepX = 1;
			all->ray.sidedistX = (all->ray.mapX + 1.0 - all->info.posX) * all->ray.deltadistX;
		}
		if(all->ray.raydirY < 0)
		{
			all->ray.stepY = -1;
			all->ray.sidedistY = (all->info.posY - all->ray.mapY) * all->ray.deltadistY;
		}
		else
		{
			all->ray.stepY = 1;
			all->ray.sidedistY = (all->ray.mapY + 1.0 - all->info.posY) * all->ray.deltadistY;
		}
		//perform DDA
		while (all->ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(all->ray.sidedistX < all->ray.sidedistY)
			{
				all->ray.sidedistX += all->ray.deltadistX;
				all->ray.mapX += all->ray.stepX;
				all->ray.side = 0;
			}
			else
			{
				all->ray.sidedistY += all->ray.deltadistY;
				all->ray.mapY += all->ray.stepY;
				all->ray.side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[all->ray.mapX][all->ray.mapY] > 0)
				all->ray.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(all->ray.side == 0)
			all->ray.perpwalldist = (all->ray.mapX - all->info.posX + (1 - all->ray.stepX) / 2) / all->ray.raydirX;
		else
			all->ray.perpwalldist = (all->ray.mapY - all->info.posY + (1 - all->ray.stepY) / 2) / all->ray.raydirY;
		//Calculate height of line to draw on screen
		all->ray.lineheight = (int)(height / all->ray.perpwalldist);
		//calculate lowest and highest pixel to fill in current stripe
		all->ray.drawstart = -all->ray.lineheight / 2 + height / 2;
		if(all->ray.drawstart < 0)
			all->ray.drawstart = 0;
		all->ray.drawend = all->ray.lineheight / 2 + height / 2;
		if(all->ray.drawend >= height)
			all->ray.drawend = height - 1;
		//texturing calculations
		all->tex.texnum = worldMap[all->ray.mapX][all->ray.mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		//calculate value of wallX
		if (all->ray.side == 0)
			all->ray.wallX = all->info.posY + all->ray.perpwalldist * all->ray.raydirY;
		else
			all->ray.wallX = all->info.posX + all->ray.perpwalldist * all->ray.raydirX;
		all->ray.wallX -= floor(all->ray.wallX);
		//x coordinate on the texture
		all->tex.texX1 = (int)(all->ray.wallX * (double)texWidth);
		if(all->ray.side == 0 && all->ray.raydirX > 0)
			all->tex.texX1 = texWidth - all->tex.texX1 - 1;
		if(all->ray.side == 1 && all->ray.raydirY < 0)
			all->tex.texX1 = texWidth - all->tex.texX1 - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		all->tex.step = 1.0 * texHeight / all->ray.lineheight;
		// Starting texture coordinate
		all->tex.texpos = (all->ray.drawstart - height / 2 + all->ray.lineheight / 2) * all->tex.step;
		y = all->ray.drawstart;
		while (y < all->ray.drawend)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			all->tex.texY1 = (int)all->tex.texpos & (texHeight - 1);
			all->tex.texpos += all->tex.step;
			all->tex.color2 = all->info.texture[all->tex.texnum][texHeight * all->tex.texY1 + all->tex.texX1];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(all->ray.side == 1)
				all->tex.color2 = (all->tex.color2 >> 1) & 8355711;
			all->info.buf[y][x] = all->tex.color2;
			y++;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		all->info.zBuffer[x] = all->ray.perpwalldist; //perpendicular distance is used
	}

	//SPRITE CASTING
	//sort sprites from far to close
	//遠いスプライトから順に配列に格納
	i = 0;
	while (i < numSprites)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((all->info.posX - sprite[i].x) * (all->info.posX - sprite[i].x) + (all->info.posY - sprite[i].y) * (all->info.posY - sprite[i].y)); //sqrt not taken, unneeded
		i++;
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);
	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < numSprites)
	{
		//translate sprite position to relative to camera
		all->spr.spriteX = sprite[spriteOrder[i]].x - all->info.posX;
		all->spr.spriteY = sprite[spriteOrder[i]].y - all->info.posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		all->spr.invDet = 1.0 / (all->info.planeX * all->info.dirY - all->info.dirX * all->info.planeY); //required for correct matrix multiplication

		all->spr.transformX = all->spr.invDet * (all->info.dirY * all->spr.spriteX - all->info.dirX * all->spr.spriteY);
		all->spr.transformY = all->spr.invDet * (-all->info.planeY * all->spr.spriteX + all->info.planeX * all->spr.spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		all->spr.spriteScreenX = (int)((width / 2) * (1 + all->spr.transformX / all->spr.transformY));

		all->spr.vMoveScreen = (int)(vMove / all->spr.transformY);

		//calculate height of the sprite on screen
		all->spr.spriteHeight = (int)fabs((height / all->spr.transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		all->spr.drawStartY = -all->spr.spriteHeight / 2 + height / 2 + all->spr.vMoveScreen;
		if(all->spr.drawStartY < 0)
			all->spr.drawStartY = 0;
		all->spr.drawEndY = all->spr.spriteHeight / 2 + height / 2 + all->spr.vMoveScreen;
		if(all->spr.drawEndY >= height)
			all->spr.drawEndY = height - 1;

		//calculate width of the sprite
		all->spr.spriteWidth = (int)fabs((height / all->spr.transformY) / uDiv);
		all->spr.drawStartX = -all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
		if(all->spr.drawStartX < 0)
			all->spr.drawStartX = 0;
		all->spr.drawEndX = all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
		if(all->spr.drawEndX >= width)
			all->spr.drawEndX = width - 1;

		//loop through every vertical stripe of the sprite on screen
		stripe = all->spr.drawStartX;
		while (stripe < all->spr.drawEndX)
		{
			all->spr.texX = (int)((256 * (stripe - (-all->spr.spriteWidth / 2 + all->spr.spriteScreenX)) * texWidth / all->spr.spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (all->spr.transformY > 0 && stripe > 0 && stripe < width && all->spr.transformY < all->info.zBuffer[stripe])
			{
				y = all->spr.drawStartY;
				while (y < all->spr.drawEndY) //for every pixel of the current stripe
				{
					all->spr.d = (y-all->spr.vMoveScreen) * 256 - height * 128 + all->spr.spriteHeight * 128; //256 and 128 factors to avoid floats
					all->spr.texY = ((all->spr.d * texHeight) / all->spr.spriteHeight) / 256;
					all->spr.color3 = all->info.texture[sprite[spriteOrder[i]].texture][texWidth * all->spr.texY + all->spr.texX]; //get current color from the texture
					if((all->spr.color3 & 0x00FFFFFF) != 0) all->info.buf[y][stripe] = all->spr.color3; //paint pixel if it isn't black, black is the invisible color
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

int	main_loop(t_all *all)
{
	calc(all);
	draw(all);
	key_update(all);
	return (0);
}

void	key_update(t_all *all)
{
	if (all->info.key_w)
	{
		if (!worldMap[(int)(all->info.posX + all->info.dirX * all->info.moveSpeed)][(int)(all->info.posY)])
			all->info.posX += all->info.dirX * all->info.moveSpeed;
		if (!worldMap[(int)(all->info.posX)][(int)(all->info.posY + all->info.dirY * all->info.moveSpeed)])
			all->info.posY += all->info.dirY * all->info.moveSpeed;
	}
	//move backwards if no wall behind you
	if (all->info.key_s)
	{
		if (!worldMap[(int)(all->info.posX - all->info.dirX * all->info.moveSpeed)][(int)(all->info.posY)])
			all->info.posX -= all->info.dirX * all->info.moveSpeed;
		if (!worldMap[(int)(all->info.posX)][(int)(all->info.posY - all->info.dirY * all->info.moveSpeed)])
			all->info.posY -= all->info.dirY * all->info.moveSpeed;
	}
	//rotate to the right
	if (all->info.key_d)
	{
		//both camera direction and camera plane must be rotated
		all->ray.olddirX = all->info.dirX;
		all->info.dirX = all->info.dirX * cos(-all->info.rotSpeed) - all->info.dirY * sin(-all->info.rotSpeed);
		all->info.dirY = all->ray.olddirX * sin(-all->info.rotSpeed) + all->info.dirY * cos(-all->info.rotSpeed);
		all->ray.oldplaneX = all->info.planeX;
		all->info.planeX = all->info.planeX * cos(-all->info.rotSpeed) - all->info.planeY * sin(-all->info.rotSpeed);
		all->info.planeY = all->ray.oldplaneX * sin(-all->info.rotSpeed) + all->info.planeY * cos(-all->info.rotSpeed);
	}
	//rotate to the left
	if (all->info.key_a)
	{
		//both camera direction and camera plane must be rotated
		all->ray.olddirX = all->info.dirX;
		all->info.dirX = all->info.dirX * cos(all->info.rotSpeed) - all->info.dirY * sin(all->info.rotSpeed);
		all->info.dirY = all->ray.olddirX * sin(all->info.rotSpeed) + all->info.dirY * cos(all->info.rotSpeed);
		all->ray.oldplaneX = all->info.planeX;
		all->info.planeX = all->info.planeX * cos(all->info.rotSpeed) - all->info.planeY * sin(all->info.rotSpeed);
		all->info.planeY = all->ray.oldplaneX * sin(all->info.rotSpeed) + all->info.planeY * cos(all->info.rotSpeed);
	}
	if (all->info.key_esc)
		exit(0);
}

int		key_press(int key, t_all *all)
{
	if (key == K_ESC)
		exit(0);
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

int		key_release(int key, t_all *all)
{
	if (key == K_ESC)
		exit(0);
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

void	load_image(t_all *all, int *texture, char *path)
{
	int		x;
	int		y;

	all->img.img = mlx_xpm_file_to_image(all->info.mlx, path, &all->img.img_width, &all->img.img_height);
	all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian);
	y = 0;
	while (y < all->img.img_height)
	{
		x = 0;
		while (x < all->img.img_width)
		{
			texture[all->img.img_width * y + x] = all->img.data[all->img.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(all->info.mlx, all->img.img);
}

void	load_texture(t_all *all)
{
	load_image(all, all->info.texture[0], "textures/eagle.xpm");
	load_image(all, all->info.texture[1], "textures/redbrick.xpm");
	load_image(all, all->info.texture[2], "textures/purplestone.xpm");
	load_image(all, all->info.texture[3], "textures/greystone.xpm");
	load_image(all, all->info.texture[4], "textures/bluestone.xpm");
	load_image(all, all->info.texture[5], "textures/mossy.xpm");
	load_image(all, all->info.texture[6], "textures/wood.xpm");
	load_image(all, all->info.texture[7], "textures/colorstone.xpm");
	load_image(all, all->info.texture[8], "textures/barrel.xpm");
	load_image(all, all->info.texture[9], "textures/pillar.xpm");
	load_image(all, all->info.texture[10], "textures/greenlight.xpm");
}


int	main(void)
{
	t_all	all;
	int		i;
	int		j;

	all.info.mlx = mlx_init();

	all.info.posX = 22.0;
	all.info.posY = 11.5;
	all.info.dirX = -1.0;
	all.info.dirY = 0.0;
	all.info.planeX = 0.0;
	all.info.planeY = 0.66;
	all.info.key_a = 0;
	all.info.key_w = 0;
	all.info.key_s = 0;
	all.info.key_d = 0;
	all.info.key_esc = 0;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
			all.info.buf[i][j++] = 0;
		i++;
	}

	if (!(all.info.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	i = 0;
	while (i < 11)
	{
		if (!(all.info.texture[i++] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < texHeight * texWidth)
			all.info.texture[i][j++] = 0;
		i++;
	}

	load_texture(&all);

	all.info.moveSpeed = 0.05;
	all.info.rotSpeed = 0.05;
	
	all.info.win = mlx_new_window(all.info.mlx, width, height, "mlx");

	all.img.img = mlx_new_image(all.info.mlx, width, height);
	all.img.data = (int *)mlx_get_data_addr(all.img.img, &all.img.bpp, &all.img.size_l, &all.img.endian);
	
	mlx_loop_hook(all.info.mlx, &main_loop, &all);
	mlx_hook(all.info.win, X_EVENT_KEY_PRESS, 0, &key_press, &all);
	mlx_hook(all.info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &all);

	mlx_loop(all.info.mlx);
}
