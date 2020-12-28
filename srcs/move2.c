/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 02:10:48 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:22:32 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_turn_left(t_all *all)
{
	all->ray.olddir_x = all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(-all->player.rotspeed)
				- all->player.dir_y * sin(-all->player.rotspeed);
	all->player.dir_y = all->ray.olddir_x * sin(-all->player.rotspeed)
				+ all->player.dir_y * cos(-all->player.rotspeed);
	all->ray.oldplane_x = all->player.plane_x;
	all->player.plane_x = all->player.plane_x * cos(-all->player.rotspeed)
				- all->player.plane_y * sin(-all->player.rotspeed);
	all->player.plane_y = all->ray.oldplane_x * sin(-all->player.rotspeed)
				+ all->player.plane_y * cos(-all->player.rotspeed);
}

void	ft_turn_right(t_all *all)
{
	all->ray.olddir_x = all->player.dir_x;
	all->player.dir_x = all->player.dir_x * cos(all->player.rotspeed)
				- all->player.dir_y * sin(all->player.rotspeed);
	all->player.dir_y = all->ray.olddir_x * sin(all->player.rotspeed)
				+ all->player.dir_y * cos(all->player.rotspeed);
	all->ray.oldplane_x = all->player.plane_x;
	all->player.plane_x = all->player.plane_x * cos(all->player.rotspeed)
				- all->player.plane_y * sin(all->player.rotspeed);
	all->player.plane_y = all->ray.oldplane_x * sin(all->player.rotspeed)
				+ all->player.plane_y * cos(all->player.rotspeed);
}
