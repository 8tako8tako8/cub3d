/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:22:27 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:23:18 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_check_after_map(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (-1);
		i++;
	}
	return (1);
}

void	ft_check_element_and_parse_map(t_all *all, char **line)
{
	all->map.start = 1;
	if (all->map.end == 1)
		ft_put_error_and_exit("Invalid map\n", all);
	if (!all->cubflag.r || !all->cubflag.no || !all->cubflag.so
	|| !all->cubflag.we || !all->cubflag.ea
	|| !all->cubflag.s || !all->cubflag.f || !all->cubflag.c)
		ft_put_error_and_exit("All elements are needed\n", all);
	ft_parse_map(all, line);
}

void	ft_parse_line(t_all *all, char **line)
{
	if ((*line)[0] == 'R' && (*line)[1] == ' ')
		ft_parse_line_r(all, line);
	else if ((*line)[0] == 'N' && (*line)[1] == 'O' && (*line)[2] == ' ')
		ft_parse_line_no(all, line);
	else if ((*line)[0] == 'S' && (*line)[1] == 'O' && (*line)[2] == ' ')
		ft_parse_line_so(all, line);
	else if ((*line)[0] == 'W' && (*line)[1] == 'E' && (*line)[2] == ' ')
		ft_parse_line_we(all, line);
	else if ((*line)[0] == 'E' && (*line)[1] == 'A' && (*line)[2] == ' ')
		ft_parse_line_ea(all, line);
	else if ((*line)[0] == 'S' && (*line)[1] == ' ')
		ft_parse_line_s(all, line);
	else if ((*line)[0] == 'F' && (*line)[1] == ' ')
		ft_parse_line_f(all, line);
	else if ((*line)[0] == 'C' && (*line)[1] == ' ')
		ft_parse_line_c(all, line);
	else if (ft_ismap(all, *line))
		ft_check_element_and_parse_map(all, line);
	else if (all->map.start == 1 && all->map.end == 0)
		all->map.end = 1;
	else if (all->map.start == 1 && all->map.end == 1
	&& ft_check_after_map(*line) == -1)
		ft_put_error_and_exit("Map is not at the end\n", all);
	else if (!ft_isonlyspace(line))
		ft_put_error_and_exit("Neither element nor map\n", all);
}
