/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 02:15:48 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/28 12:46:32 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_skip_digit(char **line, int *i, int *count)
{
	if (ft_isdigit((*line)[*i]))
		(*count)++;
	while (ft_isdigit((*line)[*i]))
		(*i)++;
}

void	ft_get_win(t_all *all, char **line, int *i)
{
	int		j;

	j = *i + 2;
	all->win_r.x = ft_atoi_ex(*line + j);
	while ((*line)[j] == ' ')
		j++;
	while (ft_isdigit((*line)[j]))
		j++;
	all->win_r.y = ft_atoi_ex(*line + j);
	while ((*line)[j] == ' ')
		j++;
	while (ft_isdigit((*line)[j]))
		j++;
	while ((*line)[j] == ' ')
		j++;
	if ((*line)[j] || all->win_r.x <= 0 || all->win_r.y <= 0)
	{
		ft_put_error_and_exit("Invalid R\n", all);
	}
}

void	ft_get_floor(t_all *all, char **line, int *i)
{
	int		count;
	int		j;

	count = 0;
	j = *i + 2;
	all->color_f.r = ft_atoi_ex(*line + j);
	while ((*line)[j] == ' ')
		j++;
	ft_skip_digit(line, &j, &count);
	if ((*line)[j] == ',')
		j++;
	all->color_f.g = ft_atoi_ex(*line + j);
	ft_skip_digit(line, &j, &count);
	if ((*line)[j] == ',')
		j++;
	all->color_f.b = ft_atoi_ex(*line + j);
	ft_skip_digit(line, &j, &count);
	while ((*line)[j] == ' ')
		j++;
	if (count != 3 || (*line)[j] || all->color_f.r < 0
	|| all->color_f.g < 0 || all->color_f.b < 0 || all->color_f.r > 255
	|| all->color_f.g > 255 || all->color_f.b > 255)
		ft_put_error_and_exit("Invalid F\n", all);
}

void	ft_get_ceiling(t_all *all, char **line, int *i)
{
	int		count;
	int		j;

	count = 0;
	j = *i + 2;
	all->color_c.r = ft_atoi_ex(*line + j);
	while ((*line)[j] == ' ')
		j++;
	ft_skip_digit(line, &j, &count);
	if ((*line)[j] == ',')
		j++;
	all->color_c.g = ft_atoi_ex(*line + j);
	ft_skip_digit(line, &j, &count);
	if ((*line)[j] == ',')
		j++;
	all->color_c.b = ft_atoi_ex(*line + j);
	ft_skip_digit(line, &j, &count);
	while ((*line)[j] == ' ')
		j++;
	if (count != 3 || (*line)[j] || all->color_c.r < 0
	|| all->color_c.g < 0 || all->color_c.b < 0 || all->color_c.r > 255
	|| all->color_c.g > 255 || all->color_c.b > 255)
		ft_put_error_and_exit("Invalid C\n", all);
}

char	*ft_get_path(char **line, t_all *all, int *i)
{
	char	*path;
	char	**tmp;
	int		j;

	j = *i + 2;
	while ((*line)[j] == ' ')
		j++;
	if (!((*line)[j]))
		ft_put_error_and_exit("There is no PATH\n", all);
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit("Invalid PATH\n", all);
	if (!(path = ft_strdup(tmp[1])) || !(path[0] == '.' && path[1] == '/'))
	{
		ft_free2(tmp);
		ft_put_error_and_exit("Invalid PATH\n", all);
	}
	if (tmp[2] != NULL)
	{
		ft_free2(tmp);
		ft_put_error_and_exit("Invalid PATH\n", all);
	}
	ft_free2(tmp);
	return (path);
}
