/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 02:12:39 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 02:19:48 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_line_s(t_all *all, char **line)
{
	if (all->cubflag.s == 0)
	{
		all->path_tex.sprite = ft_get_path(line, all);
		all->cubflag.s = 1;
	}
	else
		ft_put_error_and_exit("Set only one S\n", all);
}

void	ft_parse_line_f(t_all *all, char **line)
{
	if (all->cubflag.f == 0)
	{
		ft_get_floor(all, line);
		all->cubflag.f = 1;
	}
	else
		ft_put_error_and_exit("Set only one F\n", all);
}

void	ft_parse_line_c(t_all *all, char **line)
{
	if (all->cubflag.c == 0)
	{
		ft_get_ceiling(all, line);
		all->cubflag.c = 1;
	}
	else
		ft_put_error_and_exit("Set only one C\n", all);
}
