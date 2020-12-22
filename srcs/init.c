/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:15:31 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:20:39 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_sprite(t_all *all)
{
	all->spr.num = ft_lstsize_ex(all->sprlst);
	all->spr.sprite_x = (double *)malloc(sizeof(double) * all->spr.num);
	all->spr.sprite_y = (double *)malloc(sizeof(double) * all->spr.num);
}

void	ft_init_all(t_all *all, int argc)
{
	all->save = 0;
	if (argc == 3)
		all->save = 1;
	all->cubflag.r = 0;
	all->cubflag.no = 0;
	all->cubflag.so = 0;
	all->cubflag.we = 0;
	all->cubflag.ea = 0;
	all->cubflag.s = 0;
	all->cubflag.f = 0;
	all->cubflag.c = 0;
	all->cubflag.mlx_start = 0;
	all->map.start = 0;
	all->map.end = 0;
	all->spr.sprite_x = NULL;
	all->spr.sprite_y = NULL;
	all->spr.zbuffer = NULL;
	all->sprlst = NULL;
	all->win_r.x = 0;
	all->win_r.y = 0;
	all->start_point.flag = 0;
	all->img.img = NULL;
	all->mlx.mlx = NULL;
	all->player.speed = 0.005;
	all->player.rotspeed = 0.005;
}

void	ft_init_key_and_path(t_all *all)
{
	all->key.key_a = 0;
	all->key.key_w = 0;
	all->key.key_s = 0;
	all->key.key_d = 0;
	all->key.key_esc = 0;
	all->key.key_left = 0;
	all->key.key_right = 0;
	all->path_tex.north = NULL;
	all->path_tex.south = NULL;
	all->path_tex.west = NULL;
	all->path_tex.east = NULL;
	all->path_tex.sprite = NULL;
}

void	ft_init_map(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
				all->map.charmap[i][j] = 'x';
			else
				all->map.charmap[i][j] = '4';
			j++;
		}
		i++;
	}
}

void	ft_init(t_all *all, int argc)
{
	ft_init_all(all, argc);
	ft_init_key_and_path(all);
	ft_init_map(all);
}
