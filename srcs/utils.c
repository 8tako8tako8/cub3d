/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:15:50 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 02:23:12 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double  	ft_decimals(double value)
{
    double  ret_decimals;

    ret_decimals = value - (int)value;
    return ret_decimals;
}

double		ft_floor(double value)
{
    double  ret_int;

    if (value < 0)
    {
        if (value < value - ft_decimals(value))
            ret_int = value - ft_decimals(value) - 1;
        else
            ret_int = (int)value;
    }
    else
        ret_int = (int)value;
    return (ret_int);
}

double		ft_absolute_value(double value)
{
	if (value < 0)
		value *= -1;
	return (value);
}

void		ft_free2(char **dst)
{
	int		i;
	int		num;

	if (dst == NULL)
		return ;
	num = 0;
	while (dst[num])
		num++;
	i = 0;
	while (i < num)
	{
		if (dst[i])
			free(dst[i]);
		i++;
	}
	if (dst)
		free(dst);
}

void		ft_free(int **dst, int i)
{
	if (dst == NULL)
		return ;
	while (i > 0)
	{
		i--;
		if (dst[i])
			free(dst[i]);
	}
	if (dst)
		free(dst);
}