/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:22:27 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/28 15:22:53 by kmorimot         ###   ########.fr       */
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

int		ft_check_null_and_space(char **line, int *i)
{
	if (!((*line)[*i]))
		return (-1);
	while ((*line)[*i] == ' ')
		(*i)++;
	if (!((*line)[*i]) || !((*line)[*i + 1]) || !((*line)[*i + 2]))
		return (-1);
	return (1);
}

void	ft_check_element_and_parse_map(t_all *all, char **line)
{
	all->map.start = 1;
	if (all->map.end == 1)
		ft_put_error_and_exit("Invalid map\n", all);
	if (!all->flag.r || !all->flag.no || !all->flag.so
	|| !all->flag.we || !all->flag.ea
	|| !all->flag.s || !all->flag.f || !all->flag.c)
		ft_put_error_and_exit("All elements are needed\n", all);
	ft_parse_map(all, line);
}

void	ft_parse_line_elem(t_all *all, char **line)
{
	int		i;

	i = 0;
	if (ft_check_null_and_space(line, &i) == -1)
		return ;
	if ((*line)[i] == 'R' && (*line)[i + 1] == ' ')
		ft_parse_line_r(all, line, &i);
	else if ((*line)[i] == 'N' && (*line)[i + 1] == 'O'
	&& (*line)[i + 2] == ' ')
		ft_parse_line_no(all, line, &i);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == 'O'
	&& (*line)[i + 2] == ' ')
		ft_parse_line_so(all, line, &i);
	else if ((*line)[i] == 'W' && (*line)[i + 1] == 'E'
	&& (*line)[i + 2] == ' ')
		ft_parse_line_we(all, line, &i);
	else if ((*line)[i] == 'E' && (*line)[i + 1] == 'A'
	&& (*line)[i + 2] == ' ')
		ft_parse_line_ea(all, line, &i);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == ' ')
		ft_parse_line_s(all, line, &i);
	else if ((*line)[i] == 'F' && (*line)[i + 1] == ' ')
		ft_parse_line_f(all, line, &i);
	else if ((*line)[i] == 'C' && (*line)[i + 1] == ' ')
		ft_parse_line_c(all, line, &i);
}

void	ft_parse_line(t_all *all, char **line)
{
	ft_parse_line_elem(all, line);
	if (all->flag.eflag == 0 && ft_ismap(all, *line))
		ft_check_element_and_parse_map(all, line);
	else if (all->flag.eflag == 0 && all->map.start == 1 && all->map.end == 0)
		all->map.end = 1;
	else if (all->flag.eflag == 0 && all->map.start == 1 && all->map.end == 1
	&& ft_check_after_map(*line) == -1)
		ft_put_error_and_exit("Map is not at the end\n", all);
	else if (all->flag.eflag == 0 && !ft_isonlyspace(line))
		ft_put_error_and_exit("Neither element nor map\n", all);
	all->flag.eflag = 0;
}
