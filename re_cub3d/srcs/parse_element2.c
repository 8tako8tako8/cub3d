/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 02:12:39 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/28 12:46:41 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_parse_line_s(t_all *all, char **line, int *i)
{
	if (all->flag.s == 0)
	{
		all->flag.eflag = 1;
		all->path_tex.sprite = ft_get_path(line, all, i);
		all->flag.s = 1;
	}
	else
		ft_put_error_and_exit("Set only one S\n", all);
}

void	ft_parse_line_f(t_all *all, char **line, int *i)
{
	if (all->flag.f == 0)
	{
		all->flag.eflag = 1;
		ft_get_floor(all, line, i);
		all->flag.f = 1;
	}
	else
		ft_put_error_and_exit("Set only one F\n", all);
}

void	ft_parse_line_c(t_all *all, char **line, int *i)
{
	if (all->flag.c == 0)
	{
		all->flag.eflag = 1;
		ft_get_ceiling(all, line, i);
		all->flag.c = 1;
	}
	else
		ft_put_error_and_exit("Set only one C\n", all);
}
