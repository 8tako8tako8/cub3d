/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:37:47 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 16:14:03 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_int_overflow(int sign, const char *str)
{
	int		digit;

	digit = 0;
	while (ft_isdigit(str[digit]))
		digit++;
	if (digit > 10)
		return (-1);
	if ((sign == 1 && ft_strncmp(str, "2147483647", 19) > 0)
		&& digit == 10)
		return (-1);
	if ((sign == -1 && ft_strncmp(str, "2147483648", 19) > 0)
		&& digit == 10)
		return (-1);
	return (1);
}

int			ft_atoi_ex(const char *str)
{
	long long		number;
	int				sign;
	int				i;

	number = 0;
	sign = 1;
	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (check_int_overflow(sign, str + i) == -1)
		return (check_int_overflow(sign, str + i));
	while (ft_isdigit(str[i]))
	{
		number = number * 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}

int			ft_strchr_ex(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return (1);
	return (0);
}
