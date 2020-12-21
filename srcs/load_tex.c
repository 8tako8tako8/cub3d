/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:18:33 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 02:05:35 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_image(t_all *all, char *path)
{
	int			x;
	int			y;
	static int	i;

	if (!(all->img.img = mlx_xpm_file_to_image(all->mlx.mlx, path, 
									&all->img.img_width, &all->img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->img.data = (int *)mlx_get_data_addr(all->img.img, 
							&all->img.bpp, &all->img.size_l, &all->img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	if (!(all->mlx.texture[i] = (int *)malloc(sizeof(int) 
								* (all->img.img_height * all->img.img_width))))
		ft_put_error_and_exit("Cannot allocate memory\n", all);
	x = 0;
	while (x < all->img.img_height * all->img.img_width)
		all->mlx.texture[i][x++] = 0;
	y = 0;
	while (y < all->img.img_height)
	{
		x = 0;
		while (x < all->img.img_width)
		{
			all->mlx.texture[i][all->img.img_width * y + x] 
							= all->img.data[all->img.size_l / 4 * y + x];
			x++;
		}
		y++;
	}
	all->img.tex_width[i] = all->img.img_width;
	all->img.tex_height[i] = all->img.img_height;
	i++;
	mlx_destroy_image(all->mlx.mlx, all->img.img);
}

void	ft_load_texture(t_all *all)
{
	ft_load_image(all, all->path_tex.west);
	ft_load_image(all, all->path_tex.north);
	ft_load_image(all, all->path_tex.south);
	ft_load_image(all, all->path_tex.east);
	ft_load_image(all, all->path_tex.sprite);
}