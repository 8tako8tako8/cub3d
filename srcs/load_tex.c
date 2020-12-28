/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:18:33 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/23 17:04:49 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* void	ft_load_image2(t_all *all, int i)
{
	int		x;
	int		y;

	y = 0;
	while (y < all->img.img_height)
	{
		x = 0;
		while (x < all->img.img_width)
		{
			all->mlx.texture[i][all->img.img_width * y\
			+ (all->img.img_width - (x + 1))] =\
				all->img.data[(all->img.size_l / (all->img.bpp / 8)) * y + x];
			x++;
		}
		y++;
	}
}

void	ft_load_image(t_all *all, char *path)
{
	int			x;
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
	ft_load_image2(all, i);
	all->img.tex_width[i] = all->img.img_width;
	all->img.tex_height[i] = all->img.img_height;
	i++;
	mlx_destroy_image(all->mlx.mlx, all->img.img);
} */

void	ft_load_texture(t_all *all)
{
	if (!(all->no_img.img = mlx_xpm_file_to_image(all->mlx.mlx, all->path_tex.north,
					&all->no_img.img_width, &all->no_img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->no_img.data = (int *)mlx_get_data_addr(all->no_img.img,
					&all->no_img.bpp, &all->no_img.size_l, &all->no_img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	if (!(all->so_img.img = mlx_xpm_file_to_image(all->mlx.mlx, all->path_tex.south,
					&all->so_img.img_width, &all->so_img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->so_img.data = (int *)mlx_get_data_addr(all->so_img.img,
					&all->so_img.bpp, &all->so_img.size_l, &all->so_img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	if (!(all->we_img.img = mlx_xpm_file_to_image(all->mlx.mlx, all->path_tex.west,
					&all->we_img.img_width, &all->we_img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->we_img.data = (int *)mlx_get_data_addr(all->we_img.img,
					&all->we_img.bpp, &all->we_img.size_l, &all->we_img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	if (!(all->ea_img.img = mlx_xpm_file_to_image(all->mlx.mlx, all->path_tex.east,
					&all->ea_img.img_width, &all->ea_img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->ea_img.data = (int *)mlx_get_data_addr(all->ea_img.img,
					&all->ea_img.bpp, &all->ea_img.size_l, &all->ea_img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
	if (!(all->s_img.img = mlx_xpm_file_to_image(all->mlx.mlx, all->path_tex.sprite,
					&all->s_img.img_width, &all->s_img.img_height)))
		ft_put_error_and_exit("Invalid path\n", all);
	if (!(all->s_img.data = (int *)mlx_get_data_addr(all->s_img.img,
					&all->s_img.bpp, &all->s_img.size_l, &all->s_img.endian)))
		ft_put_error_and_exit("mlx_get_data_addr failed\n", all);
}
