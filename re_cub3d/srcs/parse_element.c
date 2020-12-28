/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:23:12 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/28 12:39:45 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_parse_line_r(t_all *all, char **line, int *i)
{
	if (all->flag.r == 0)
	{
		all->flag.eflag = 1;
		ft_get_win(all, line, i);
		all->flag.r = 1;
	}
	else
		ft_put_error_and_exit("Set only one R\n", all);
}

void	ft_parse_line_no(t_all *all, char **line, int *i)
{
	if (all->flag.no == 0)
	{
		all->flag.eflag = 1;
		all->path_tex.north = ft_get_path(line, all, i);
		all->flag.no = 1;
	}
	else
		ft_put_error_and_exit("Set only one NO\n", all);
}

void	ft_parse_line_so(t_all *all, char **line, int *i)
{
	if (all->flag.so == 0)
	{
		all->flag.eflag = 1;
		all->path_tex.south = ft_get_path(line, all, i);
		all->flag.so = 1;
	}
	else
		ft_put_error_and_exit("Set only one SO\n", all);
}

void	ft_parse_line_we(t_all *all, char **line, int *i)
{
	if (all->flag.we == 0)
	{
		all->flag.eflag = 1;
		all->path_tex.west = ft_get_path(line, all, i);
		all->flag.we = 1;
	}
	else
		ft_put_error_and_exit("Set only one WE\n", all);
}

void	ft_parse_line_ea(t_all *all, char **line, int *i)
{
	if (all->flag.ea == 0)
	{
		all->flag.eflag = 1;
		all->path_tex.east = ft_get_path(line, all, i);
		all->flag.ea = 1;
	}
	else
		ft_put_error_and_exit("Set only one EA\n", all);
}
