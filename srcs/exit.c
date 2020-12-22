/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:16:49 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:19:31 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_put_error_and_exit(char *s, t_all *all)
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

int		ft_exit(t_all *all)
{
	ft_free_path(all);
	if (all->cubflag.mlx_start == 1)
	{
		if (all->img.img)
			mlx_destroy_image(all->mlx.mlx, all->img.img);
		if (all->mlx.mlx)
		{
			mlx_destroy_display(all->mlx.mlx);
			free(all->mlx.mlx);
		}
		ft_lstclear_ex(&(all->sprlst));
		ft_free(all->win_r.buf, all->win_r.y);
		ft_free(all->mlx.texture, 5);
		if (all->spr.sprite_x)
			free(all->spr.sprite_x);
		if (all->spr.sprite_y)
			free(all->spr.sprite_y);
		if (all->spr.zbuffer)
			free(all->spr.zbuffer);
	}
	exit(0);
}
