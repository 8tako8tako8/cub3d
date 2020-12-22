/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 02:26:22 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:24:47 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_calc_wall_tex(t_all *all, int *x)
{
	int	y;

	all->tex.tex_x = (int)(all->ray.wall_x
			* (double)(all->img.tex_width[all->tex.num]));
	if (all->ray.side == 0 && all->ray.raydir_x > 0)
		all->tex.tex_x = all->img.tex_width[all->tex.num] - all->tex.tex_x - 1;
	if (all->ray.side == 1 && all->ray.raydir_y < 0)
		all->tex.tex_x = all->img.tex_width[all->tex.num] - all->tex.tex_x - 1;
	all->tex.step = 1.0 * all->img.tex_height[all->tex.num]
							/ all->ray.lineheight;
	all->tex.pos = (all->ray.drawstart - all->win_r.y / 2
				+ all->ray.lineheight / 2) * all->tex.step;
	y = all->ray.drawstart;
	while (y < all->ray.drawend)
	{
		all->tex.tex_y = ft_min((int)all->tex.pos,
				(all->img.tex_height[all->tex.num] - 1));
		all->tex.pos += all->tex.step;
		all->tex.color = all->mlx.texture[all->tex.num]\
					[(all->img.tex_height[all->tex.num])
							* (all->tex.tex_y) + all->tex.tex_x];
		all->win_r.buf[y][*x] = all->tex.color;
		y++;
	}
}

void	ft_set_tex_for_each_direction(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydir_x < 0)
		all->tex.num = 0;
	else if (all->ray.side == 0 && all->ray.raydir_x >= 0)
		all->tex.num = 3;
	else if (all->ray.side == 1 && all->ray.raydir_y < 0)
		all->tex.num = 1;
	else if (all->ray.side == 1 && all->ray.raydir_y >= 0)
		all->tex.num = 2;
}
