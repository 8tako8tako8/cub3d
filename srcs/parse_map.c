/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:22:40 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/28 17:48:31 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_set_start_point(t_all *all, char **line, int *i, int *j)
{
	if (all->start_point.flag == 1)
		ft_put_error_and_exit("There are multiple start points\n", all);
	all->start_point.dir = (*line)[*j];
	all->start_point.flag = 1;
	all->start_point.y = *i + 1.5;
	all->start_point.x = *j + 1.5;
	all->map.charmap[*i + 1][*j + 1] = 'n';
}

void	ft_parse_map(t_all *all, char **line)
{
	static int		i = 0;
	int				j;
	static int		numline = 0;

	if ((++numline > MAP_HEIGHT - 2) || (ft_strlen(*line) > MAP_WIDTH - 2))
		ft_put_error_and_exit("Map size limit is exceeded\n", all);
	j = 0;
	while ((*line)[j] != '\0')
	{
		if ((*line)[j] == 'N' || (*line)[j] == 'S' || (*line)[j] == 'W'
		|| (*line)[j] == 'E')
			ft_set_start_point(all, line, &i, &j);
		else if ((*line)[j] == '2')
		{
			ft_lstadd_back_ex(&(all->sprlst),
				ft_newspr(j + 1.5, MAP_HEIGHT - i - 1.5));
			all->map.charmap[i + 1][j + 1] = (*line)[j];
		}
		else if ((*line)[j] == '0' || (*line)[j] == '1' || (*line)[j] == ' ')
			all->map.charmap[i + 1][j + 1] = (*line)[j];
		else
			ft_put_error_and_exit("Invalid map\n", all);
		j++;
	}
	i++;
}

int		ft_ismap(t_all *all, char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (0);
	if (ft_strchr_ex(line, '0') || ft_strchr_ex(line, '1'))
	{
		while (line[i])
		{
			if (line[i] != '0' && line[i] != '1' && line[i] != '2'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != ' ')
			{
				if (all->map.start)
				{
					ft_put_error_and_exit("Invalid map\n", all);
				}
			}
			i++;
		}
		return (1);
	}
	return (0);
}
