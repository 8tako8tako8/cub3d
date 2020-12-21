/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:23:12 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 02:19:41 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_line_r(t_all *all, char **line)
{
	if (all->cubflag.r == 0)
	{
		ft_get_win(all, line);
		all->cubflag.r = 1;
	}
	else
		ft_put_error_and_exit("Set only one R\n", all);
}

void	ft_parse_line_no(t_all *all, char **line)
{
	if (all->cubflag.no == 0)
	{
		all->path_tex.north = ft_get_path(line, all);
		all->cubflag.no = 1;
	}
	else
		ft_put_error_and_exit("Set only one NO\n", all);
}

void	ft_parse_line_so(t_all *all, char **line)
{
	if (all->cubflag.so == 0)
	{
		all->path_tex.south = ft_get_path(line, all);
		all->cubflag.so = 1;
	}
	else
		ft_put_error_and_exit("Set only one SO\n", all);
}

void	ft_parse_line_we(t_all *all, char **line)
{
	if (all->cubflag.we == 0)
	{
		all->path_tex.west = ft_get_path(line, all);
		all->cubflag.we = 1;
	}
	else
		ft_put_error_and_exit("Set only one WE\n", all);
}

void	ft_parse_line_ea(t_all *all, char **line)
{
	if (all->cubflag.ea == 0)
	{
		all->path_tex.east = ft_get_path(line, all);
		all->cubflag.ea = 1;
	}
	else
		ft_put_error_and_exit("Set only one EA\n", all);
}