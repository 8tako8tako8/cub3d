/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:32:08 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 19:56:47 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_sprite_tex2(t_all *all, int *x)
{
	int		y;

	y = all->spr.draw_start_y;
	while (y < all->spr.draw_end_y)
	{
		all->spr.d = y * 256
				- all->win_r.y * 128 + all->spr.spr_height * 128;
		all->spr.tex_y = ((all->spr.d * all->img.tex_height[4])
						/ all->spr.spr_height) / 256;
		all->spr.color = all->mlx.texture[4][all->img.tex_width[4]
						* all->spr.tex_y + all->spr.tex_x];
		if ((all->spr.color & 0xFFFFFF) != 0)
			all->win_r.buf[y][*x] = all->spr.color;
		y++;
	}
}

void	ft_calc_sprite_tex(t_all *all)
{
	int		x;

	x = all->spr.draw_start_x;
	while (x < all->spr.draw_end_x)
	{
		all->spr.tex_x = (int)((256 * (x - (-all->spr.spr_width / 2
			+ all->spr.spr_screen_x)) * all->img.tex_width[4]
			/ all->spr.spr_width) / 256);
		if (all->spr.transform_y > 0 && x > 0 && x < all->win_r.x
		&& all->spr.transform_y < all->spr.zbuffer[x])
			ft_calc_sprite_tex2(all, &x);
		x++;
	}
}

void	ft_calc_sprite_drawing(t_all *all)
{
	all->spr.spr_height = (int)ft_absolute_value((all->win_r.y
					/ all->spr.transform_y) / 1.0);
	all->spr.draw_start_y = -all->spr.spr_height / 2
				+ all->win_r.y / 2;
	if (all->spr.draw_start_y < 0)
		all->spr.draw_start_y = 0;
	all->spr.draw_end_y = all->spr.spr_height / 2
				+ all->win_r.y / 2;
	if (all->spr.draw_end_y >= all->win_r.y)
		all->spr.draw_end_y = all->win_r.y - 1;
	all->spr.spr_width = (int)ft_absolute_value((all->win_r.y
					/ all->spr.transform_y) / 1.0);
	all->spr.draw_start_x = -all->spr.spr_width / 2 + all->spr.spr_screen_x;
	if (all->spr.draw_start_x < 0)
		all->spr.draw_start_x = 0;
	all->spr.draw_end_x = all->spr.spr_width / 2 + all->spr.spr_screen_x;
	if (all->spr.draw_end_x >= all->win_r.x)
		all->spr.draw_end_x = all->win_r.x - 1;
}

void	ft_set_elements_for_sprite_drawing(t_all *all, int *i)
{
	all->spr.relative_x = all->spr.sprite_x[*i] - all->player.pos_x;
	all->spr.relative_y = all->spr.sprite_y[*i] - all->player.pos_y;
	all->spr.invdet = 1.0 / (all->player.plane_x * all->player.dir_y
				- all->player.dir_x * all->player.plane_y);
	all->spr.transform_x = all->spr.invdet * (all->player.dir_y
		* all->spr.relative_x - all->player.dir_x * all->spr.relative_y);
	all->spr.transform_y = all->spr.invdet
				* (-all->player.plane_y * all->spr.relative_x
				+ all->player.plane_x * all->spr.relative_y);
	all->spr.spr_screen_x = (int)((all->win_r.x / 2)
		* (1 + all->spr.transform_x / all->spr.transform_y));
}

void	ft_sprite_casting(t_all *all)
{
	int			i;
	t_sprlst	*sprite;

	all->sprlst = ft_lst_merge_sort(all->sprlst,
			all->player.pos_x, all->player.pos_y);
	sprite = all->sprlst;
	i = 0;
	while (i < all->spr.num)
	{
		all->spr.sprite_x[i] = sprite->x;
		all->spr.sprite_y[i] = sprite->y;
		sprite = sprite->next;
		i++;
	}
	i = 0;
	while (i < all->spr.num)
	{
		ft_set_elements_for_sprite_drawing(all, &i);
		ft_calc_sprite_drawing(all);
		ft_calc_sprite_tex(all);
		i++;
	}
}
