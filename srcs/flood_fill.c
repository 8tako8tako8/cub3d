/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:23:34 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/28 01:56:07 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_reverse_map_to_y(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			all->map.map[i][j] = all->map.r_map[MAP_HEIGHT - i - 1][j];
			j++;
		}
		i++;
	}
	all->start_point.y = MAP_HEIGHT - all->start_point.y;
}

void	ft_convert_map_char_to_int(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (all->map.charmap[i][j] == 'o')
				all->map.r_map[i][j] = 0;
			else if (all->map.charmap[i][j] == '@')
				all->map.r_map[i][j] = 2;
			else
				all->map.r_map[i][j] = 1;
			j++;
		}
		i++;
	}
}

void	ft_flood_fill_recursion(t_all *all, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if (x > MAP_WIDTH - 1 || y > MAP_HEIGHT - 1)
		return ;
	if (all->map.charmap[y][x] == ' ')
		ft_put_error_and_exit("There is space in the walking range\n", all);
	if (all->map.charmap[y][x] != '0' && all->map.charmap[y][x] != 'n'
	&& all->map.charmap[y][x] != '1' && all->map.charmap[y][x] != '2'
	&& all->map.charmap[y][x] != 'o' && all->map.charmap[y][x] != '@')
		ft_put_error_and_exit("Map is not closed\n", all);
	if (all->map.charmap[y][x] != '0' && all->map.charmap[y][x] != 'n'
	&& all->map.charmap[y][x] != '2')
		return ;
	if (all->map.charmap[y][x] == '2')
		all->map.charmap[y][x] = '@';
	else
		all->map.charmap[y][x] = 'o';
	ft_flood_fill_recursion(all, x + 1, y);
	ft_flood_fill_recursion(all, x - 1, y);
	ft_flood_fill_recursion(all, x, y + 1);
	ft_flood_fill_recursion(all, x, y - 1);
}

void	ft_flood_fill(t_all *all)
{
	ft_flood_fill_recursion(all, all->start_point.x, all->start_point.y);
	ft_convert_map_char_to_int(all);
	ft_reverse_map_to_y(all);
}
