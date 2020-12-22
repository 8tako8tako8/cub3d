/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:20:41 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:23:57 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_set_dir(t_all *all, double dir_x, double dir_y)
{
	all->player.dir_x = dir_x;
	all->player.dir_y = dir_y;
}

void	ft_set_plane(t_all *all, double plane_x, double plane_y)
{
	all->player.plane_x = plane_x;
	all->player.plane_y = plane_y;
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
}
