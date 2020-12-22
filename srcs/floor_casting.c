/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:20:08 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:19:55 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_floor_casting(t_all *all)
{
	int		x;
	int		y;

	y = all->win_r.y / 2 + 1;
	while (y < all->win_r.y)
	{
		x = 0;
		while (x < all->win_r.x)
		{
			all->win_r.buf[y][x] = all->color_f.rgb;
			all->win_r.buf[all->win_r.y - y - 1][x] = all->color_c.rgb;
			x++;
		}
		y++;
	}
}
