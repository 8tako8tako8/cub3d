/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:21:13 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/21 21:34:45 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_press_key(int key, t_all *all)
{
	if (key == K_ESC)
		ft_exit(all);
	else if (key == K_W)
		all->key.key_w = 1;
	else if (key == K_A)
		all->key.key_a = 1;
	else if (key == K_S)
		all->key.key_s = 1;
	else if (key == K_D)
		all->key.key_d = 1;
	else if (key == K_LEFT)
		all->key.key_left = 1;
	else if (key == K_RIGHT)
		all->key.key_right = 1;
	return (0);
}

int		 ft_release_key(int key, t_all *all)
{
	if (key == K_W)
		all->key.key_w = 0;
	else if (key == K_A)
		all->key.key_a = 0;
	else if (key == K_S)
		all->key.key_s = 0;
	else if (key == K_D)
		all->key.key_d = 0;
	else if (key == K_LEFT)
		all->key.key_left = 0;
	else if (key == K_RIGHT)
		all->key.key_right = 0;
	return (0);
}