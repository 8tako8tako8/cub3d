/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:16:21 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 01:37:58 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

int		ft_isspace(char c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int		ft_isonlyspace(char **line)
{
	int		i;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if (!ft_isspace((*line)[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_combine_color(t_all *all)
{
	all->color_f.rgb = all->color_f.r * 65536 + all->color_f.g * 256 + all->color_f.b;
	all->color_c.rgb = all->color_c.r * 65536 + all->color_c.g * 256 + all->color_c.b;
}