/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:18:48 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 02:11:24 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_forward(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x 
							+ all->player.dir_x * all->player.speed)])
		all->player.pos_x += all->player.dir_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y 
				+ all->player.dir_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y += all->player.dir_y * all->player.speed;
}

void	ft_move_backward(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x 
										- all->player.dir_x * all->player.speed)])
		all->player.pos_x -= all->player.dir_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y 
				- all->player.dir_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y -= all->player.dir_y * all->player.speed;
}

void	ft_move_left(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x 
									- all->player.plane_x * all->player.speed)])
		all->player.pos_x -= all->player.plane_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y 
			- all->player.plane_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y -= all->player.plane_y * all->player.speed;	
}

void	ft_move_right(t_all *all)
{
	if (!all->map.map[(int)(all->player.pos_y)][(int)(all->player.pos_x 
									+ all->player.plane_x * all->player.speed)])
		all->player.pos_x += all->player.plane_x * all->player.speed;
	if (!all->map.map[(int)(all->player.pos_y 
			+ all->player.plane_y * all->player.speed)][(int)(all->player.pos_x)])
		all->player.pos_y += all->player.plane_y * all->player.speed;	
}

void	ft_move_player(t_all *all)
{
	if (all->key.key_w)
		ft_move_forward(all);
	if (all->key.key_s)
		ft_move_backward(all);
	if (all->key.key_a)
		ft_turn_left(all);
	if (all->key.key_d)
		ft_turn_right(all);
	if (all->key.key_right)
		ft_move_right(all);
	if (all->key.key_left)
		ft_move_left(all);
}