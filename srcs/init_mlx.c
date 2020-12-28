/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:17:18 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/23 18:15:49 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
/* 	if (!(all->mlx.texture = (int **)malloc(sizeof(int *) * 5)))
		ft_put_error_and_exit("Cannot allocate memory\n", all); */
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
	if (!(all->spr.zbuffer = (double *)malloc(sizeof(double) * all->win_r.x)))
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
	mlx_get_screen_size(all->mlx.mlx, &all->win_r.screen_x,
	&all->win_r.screen_y);
	ft_resize_win_size(all);
	ft_init_buf_and_zbuffer(all);
	ft_set_pos_and_dir_and_plane(all);
	ft_init_buf_and_tex(all);
	ft_load_texture(all);
	if (all->save == 0)
		if (!(all->mlx.win = mlx_new_window(all->mlx.mlx,
		all->win_r.x, all->win_r.y, "cub3d")))
			ft_put_error_and_exit("mlx_new_window failed\n", all);
	if (!(all->img.img = mlx_new_image(all->mlx.mlx,
	all->win_r.x, all->win_r.y)))
		ft_put_error_and_exit("mlx_new_image failed\n", all);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img,
	&all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	all->cubflag.mlx_start = 1;
}
