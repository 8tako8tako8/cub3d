/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:17:48 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/21 21:27:58 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_window(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->img.data[all->img.size_l / 4 * y + x] = all->win_r.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->img.img, 0, 0);
}

int		ft_raycasting(t_all *all)
{
	ft_floor_casting(all);
	ft_wall_casting(all);
	ft_sprite_casting(all);
	ft_draw_window(all);
	ft_move_player(all);
	return (0);
}
