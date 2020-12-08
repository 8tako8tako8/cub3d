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

	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	draw(t_all *all)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			all->img.data[y * WIN_WIDTH + x] = all->info.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->info.mlx, all->info.win, all->img.img, 0, 0);
}

void	calc(t_all *all)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		stripe;

 	//FLOOR CASTING
	y = WIN_HEIGHT / 2 + 1;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// floor
			all->floor.color1 = 0x000000;
			all->info.buf[y][x] = all->floor.color1;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			all->floor.color1 = 0x0000FF;
			all->info.buf[WIN_HEIGHT - y - 1][x] = all->floor.color1;
			x++;
		}
		y++;
	}
	// WALL CASTING
	x = 0;
	while (x < WIN_WIDTH)
	{
		//calculate ray position and direction
		all->ray.cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
		all->ray.raydirX = all->info.dirX + all->info.planeX * all->ray.cameraX;
		all->ray.raydirY = all->info.dirY + all->info.planeY * all->ray.cameraX;
		//which box of the map we're in
		all->ray.mapX = (int)all->info.posX;
		all->ray.mapY = (int)all->info.posY;

		//length of ray from one x or y-side to next x or y-side
		all->ray.deltadistX = ft_absolute_value(1 / all->ray.raydirX);
		all->ray.deltadistY = ft_absolute_value(1 / all->ray.raydirY);
/* 		if ((1 / all->ray.raydirX) < 0)
			all->ray.deltadistX = - 1 / all->ray.raydirX;
		else
			all->ray.deltadistX =  1 / all->ray.raydirX; */
/* 		if ((1 / all->ray.raydirY) < 0)
			all->ray.deltadistY = - 1 / all->ray.raydirY;
		else
			all->ray.deltadistX =  1 / all->ray.raydirY; */

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
			if(all->map.map[all->ray.mapY][all->ray.mapX] == 1)
				all->ray.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(all->ray.side == 0)
			all->ray.perpwalldist = (all->ray.mapX - all->info.posX + (1 - all->ray.stepX) / 2) / all->ray.raydirX;
		else
			all->ray.perpwalldist = (all->ray.mapY - all->info.posY + (1 - all->ray.stepY) / 2) / all->ray.raydirY;
		//Calculate height of line to draw on screen
		all->ray.lineheight = (int)(WIN_HEIGHT / all->ray.perpwalldist);
		//calculate lowest and highest pixel to fill in current stripe
		all->ray.drawstart = -all->ray.lineheight / 2 + WIN_HEIGHT / 2;
		if(all->ray.drawstart < 0)
			all->ray.drawstart = 0;
		all->ray.drawend = all->ray.lineheight / 2 + WIN_HEIGHT / 2;
		if(all->ray.drawend >= WIN_HEIGHT)
			all->ray.drawend = WIN_HEIGHT - 1;
		//texturing calculations
		if (all->ray.side == 0 && all->ray.raydirX < 0)
			all->tex.texnum = 0; //1 subtracted from it so that texture 0 can be used!
		else if (all->ray.side == 0 && all->ray.raydirX >= 0)
			all->tex.texnum = 3;
		else if (all->ray.side == 1 && all->ray.raydirY < 0)
			all->tex.texnum = 1;
		else if (all->ray.side == 1 && all->ray.raydirY >= 0)
			all->tex.texnum = 2;

		//calculate value of wallX
		if (all->ray.side == 0)
			all->ray.wallX = all->info.posY + all->ray.perpwalldist * all->ray.raydirY;
		else
			all->ray.wallX = all->info.posX + all->ray.perpwalldist * all->ray.raydirX;
		all->ray.wallX -= ft_floor(all->ray.wallX);
		//x coordinate on the texture
		all->tex.texX1 = (int)(all->ray.wallX * (double)TEX_WIDTH);
		if(all->ray.side == 0 && all->ray.raydirX > 0)
			all->tex.texX1 = TEX_WIDTH - all->tex.texX1 - 1;
		if(all->ray.side == 1 && all->ray.raydirY < 0)
			all->tex.texX1 = TEX_WIDTH - all->tex.texX1 - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		all->tex.step = 1.0 * TEX_HEIGHT / all->ray.lineheight;
		// Starting texture coordinate
		all->tex.texpos = (all->ray.drawstart - WIN_HEIGHT / 2 + all->ray.lineheight / 2) * all->tex.step;
		y = all->ray.drawstart;
		while (y < all->ray.drawend)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			all->tex.texY1 = (int)all->tex.texpos & (TEX_HEIGHT - 1);
			all->tex.texpos += all->tex.step;
			all->tex.color2 = all->info.texture[all->tex.texnum][TEX_HEIGHT * all->tex.texY1 + all->tex.texX1];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(all->ray.side == 1)
				all->tex.color2 = (all->tex.color2 >> 1) & 8355711;
			all->info.buf[y][x] = all->tex.color2;
			y++;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		all->info.zBuffer[x] = all->ray.perpwalldist; //perpendicular distance is used
		x++;
	}

	//SPRITE CASTING
	//sort sprites from far to close
	//遠いスプライトから順に配列に格納

	int		spriteOrder[NUM_SPRITES];
	double	spriteDistance[NUM_SPRITES];
	i = 0;
	while (i < NUM_SPRITES)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((all->info.posX - sprite[i].x) * (all->info.posX - sprite[i].x) + (all->info.posY - sprite[i].y) * (all->info.posY - sprite[i].y)); //sqrt not taken, unneeded
		i++;
	}
	sortSprites(spriteOrder, spriteDistance, NUM_SPRITES);
	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < NUM_SPRITES)
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

		all->spr.spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + all->spr.transformX / all->spr.transformY));

		all->spr.vMoveScreen = (int)(vMove / all->spr.transformY);

		//calculate height of the sprite on screen
		all->spr.spriteHeight = (int)ft_absolute_value((WIN_HEIGHT / all->spr.transformY) / vDiv);
/* 		if (((height / all->spr.transformY) / vDiv) < 0)	
			all->spr.spriteHeight = - (int)((height / all->spr.transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		else
			all->spr.spriteHeight = (int)((height / all->spr.transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye */
		
		//calculate lowest and highest pixel to fill in current stripe
		all->spr.drawStartY = -all->spr.spriteHeight / 2 + WIN_HEIGHT / 2 + all->spr.vMoveScreen;
		if(all->spr.drawStartY < 0)
			all->spr.drawStartY = 0;
		all->spr.drawEndY = all->spr.spriteHeight / 2 + WIN_HEIGHT / 2 + all->spr.vMoveScreen;
		if(all->spr.drawEndY >= WIN_HEIGHT)
			all->spr.drawEndY = WIN_HEIGHT - 1;

		//calculate width of the sprite
		all->spr.spriteWidth = (int)ft_absolute_value((WIN_HEIGHT / all->spr.transformY) / uDiv);
/* 		if (((height / all->spr.transformY) / uDiv) < 0)
			all->spr.spriteWidth = - (int)((height / all->spr.transformY) / uDiv);
		else
			all->spr.spriteWidth = (int)((height / all->spr.transformY) / uDiv); */
		
		all->spr.drawStartX = -all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
		if(all->spr.drawStartX < 0)
			all->spr.drawStartX = 0;
		all->spr.drawEndX = all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
		if(all->spr.drawEndX >= WIN_WIDTH)
			all->spr.drawEndX = WIN_WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		stripe = all->spr.drawStartX;
		while (stripe < all->spr.drawEndX)
		{
			all->spr.texX = (int)((256 * (stripe - (-all->spr.spriteWidth / 2 + all->spr.spriteScreenX)) * TEX_WIDTH / all->spr.spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (all->spr.transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && all->spr.transformY < all->info.zBuffer[stripe])
			{
				y = all->spr.drawStartY;
				while (y < all->spr.drawEndY) //for every pixel of the current stripe
				{
					all->spr.d = (y-all->spr.vMoveScreen) * 256 - WIN_HEIGHT * 128 + all->spr.spriteHeight * 128; //256 and 128 factors to avoid floats
					all->spr.texY = ((all->spr.d * TEX_HEIGHT) / all->spr.spriteHeight) / 256;
					all->spr.color3 = all->info.texture[sprite[spriteOrder[i]].texture][TEX_WIDTH * all->spr.texY + all->spr.texX]; //get current color from the texture
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
		if (!all->map.map[(int)(all->info.posY)][(int)(all->info.posX + all->info.dirX * all->info.moveSpeed)])
			all->info.posX += all->info.dirX * all->info.moveSpeed;
		if (!all->map.map[(int)(all->info.posY + all->info.dirY * all->info.moveSpeed)][(int)(all->info.posX)])
			all->info.posY += all->info.dirY * all->info.moveSpeed;
	}
	//move backwards if no wall behind you
	if (all->info.key_s)
	{
		if (!all->map.map[(int)(all->info.posY)][(int)(all->info.posX - all->info.dirX * all->info.moveSpeed)])
			all->info.posX -= all->info.dirX * all->info.moveSpeed;
		if (!all->map.map[(int)(all->info.posY - all->info.dirY * all->info.moveSpeed)][(int)(all->info.posX)])
			all->info.posY -= all->info.dirY * all->info.moveSpeed;
	}
	//rotate to the left
	if (all->info.key_a)
	{
		//both camera direction and camera plane must be rotated
		all->ray.olddirX = all->info.dirX;
		all->info.dirX = all->info.dirX * cos(-all->info.rotSpeed) - all->info.dirY * sin(-all->info.rotSpeed);
		all->info.dirY = all->ray.olddirX * sin(-all->info.rotSpeed) + all->info.dirY * cos(-all->info.rotSpeed);
		all->ray.oldplaneX = all->info.planeX;
		all->info.planeX = all->info.planeX * cos(-all->info.rotSpeed) - all->info.planeY * sin(-all->info.rotSpeed);
		all->info.planeY = all->ray.oldplaneX * sin(-all->info.rotSpeed) + all->info.planeY * cos(-all->info.rotSpeed);
	}
	//rotate to the right
	if (all->info.key_d)
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
	load_image(all, all->info.texture[0], "west/redbrick.xpm");
	load_image(all, all->info.texture[1], "south/greystone.xpm");
	load_image(all, all->info.texture[2], "north/eagle.xpm");
	load_image(all, all->info.texture[3], "east/purplestone.xpm");
	load_image(all, all->info.texture[4], "sprite/barrel.xpm");

}

void	ft_raycasting(t_all *all)
{
	int		i;
	int		j;

	all->info.mlx = mlx_init();

	all->info.posX = 2.5;
	all->info.posY = 2.5;
	all->info.dirX = 0.0;
	all->info.dirY = -1.0;
	all->info.planeX = 0.66;
	all->info.planeY = 0.0;
	all->info.key_a = 0;
	all->info.key_w = 0;
	all->info.key_s = 0;
	all->info.key_d = 0;
	all->info.key_esc = 0;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
			all->info.buf[i][j++] = 0;
		i++;
	}

	if (!(all->info.texture = (int **)malloc(sizeof(int *) * 5)))
		return ;
	i = 0;
	while (i < 5)
	{
		if (!(all->info.texture[i++] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH))))
			return ;
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
			all->info.texture[i][j++] = 0;
		i++;
	}

	load_texture(all);

	all->info.moveSpeed = 0.05;
	all->info.rotSpeed = 0.05;
	
	all->info.win = mlx_new_window(all->info.mlx, WIN_WIDTH, WIN_HEIGHT, "mlx");

	all->img.img = mlx_new_image(all->info.mlx, WIN_WIDTH, WIN_HEIGHT);
	all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size_l, &all->img.endian);
	
	mlx_loop_hook(all->info.mlx, &main_loop, all);
	mlx_hook(all->info.win, X_EVENT_KEY_PRESS, 0, &key_press, all);
	mlx_hook(all->info.win, X_EVENT_KEY_RELEASE, 0, &key_release, all);

	mlx_loop(all->info.mlx);
}