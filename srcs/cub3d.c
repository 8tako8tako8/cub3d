/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:50:57 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/22 21:19:05 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_read_cub(t_all *all, int fd)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_parse_line(all, &line);
		free(line);
	}
	if (ret == -1)
	{
		ft_put_error_and_exit("Failed to read file\n", all);
	}
	ft_parse_line(all, &line);
	free(line);
	ft_combine_color(all);
}

int		ft_iscub(char *cub)
{
	int		len;

	len = ft_strlen(cub);
	if (len > 4 && cub[len - 1] == 'b' && cub[len - 2] == 'u'
					&& cub[len - 3] == 'c' && cub[len - 4] == '.')
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;
	int		fd;

	if (((argc == 2 && ft_iscub(argv[1]))) || (argc == 3
		&& !ft_strncmp(argv[2], "--save", 7)))
	{
		ft_init(&all, argc);
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			ft_put_error_and_exit("Failed to open file\n", &all);
		ft_read_cub(&all, fd);
		if (all.start_point.flag != 1)
			ft_put_error_and_exit("There is not a start point\n", &all);
		ft_flood_fill(&all);
		ft_init_sprite(&all);
		close(fd);
		ft_init_mlx_and_win(&all);
		if (argc == 3)
			ft_write_bmp(&all);
		mlx_loop_hook(all.mlx.mlx, &ft_raycasting, &all);
		mlx_hook(all.mlx.win, 2, 1L << 0, &ft_press_key, &all);
		mlx_hook(all.mlx.win, 3, 1L << 1, &ft_release_key, &all);
		mlx_hook(all.mlx.win, 17, 1L << 17, &ft_exit, &all);
		mlx_loop(all.mlx.mlx);
	}
	ft_put_error_and_exit("Invalid comandline arguments\n", &all);
}
