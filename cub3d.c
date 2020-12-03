/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:50:57 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/04 01:52:51 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_success_or_error(char *s, int color)
{
	if (color == 0)
	{
		write(1, "\e[31mError\e[m\n", 15);
		ft_putstr_fd(s, 1);
	}
	else if (color == 1)
	{
		write(1, "\e[32mSuccess\e[m\n", 17);
		ft_putstr_fd(s, 1);
	}
}

void	ft_get_win(t_all *all, char **line)
{
	int		i;

	i = 2;
	all->win_r.x = ft_atoi(*line + i);
	while ((*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		i++;
	all->win_r.y = ft_atoi(*line + i);
	while ((*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		i++;
	while ((*line)[i] == ' ')
		i++;
	if (all->win_r.x >= 10000)
		all->win_r.x = 9999;
	if (all->win_r.y >= 10000)
		all->win_r.y = 9999;
	if ((*line)[i] || all->win_r.x <= 0 || all->win_r.y <= 0)
	{
		ft_put_success_or_error("Invalid R\n", 0);
		exit(0);			
	}
}

void	ft_get_floor(t_all *all, char **line)
{
	int		count;
	int		i;

	count = 0;
	i = 2;
	all->color_f.r = ft_atoi(*line + i);
	while ((*line)[i] == ' ')
		i++;
	if (ft_isdigit((*line)[i]))
		count++;
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->color_f.g = ft_atoi(*line + i);
	if (ft_isdigit((*line)[i]))
		count++;
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->color_f.b = ft_atoi(*line + i);
	if (ft_isdigit((*line)[i]))
		count++;
	while (ft_isdigit((*line)[i]))
		i++;
	while ((*line)[i] == ' ')
		i++;
	if (count != 3 || (*line)[i] || all->color_f.r < 0 || all->color_f.g < 0 || all->color_f.b < 0
							|| all->color_f.r > 255 || all->color_f.g > 255 || all->color_f.b > 255)
	{
		ft_put_success_or_error("Invalid F\n", 0);
		exit(0);
	}
}

void	ft_get_ceiling(t_all *all, char **line)
{
	int		count;
	int		i;

	count = 0;
	i = 2;
	all->color_c.r = ft_atoi(*line + i);
	while ((*line)[i] == ' ')
		i++;
	if (ft_isdigit((*line)[i]))
		count++;
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->color_c.g = ft_atoi(*line + i);
	if (ft_isdigit((*line)[i]))
		count++;
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->color_c.b = ft_atoi(*line + i);
	if (ft_isdigit((*line)[i]))
		count++;
	while (ft_isdigit((*line)[i]))
		i++;
	while ((*line)[i] == ' ')
		i++;
	if (count != 3 || (*line)[i] || all->color_c.r < 0 || all->color_c.g < 0 || all->color_c.b < 0
		|| all->color_c.r > 255 || all->color_c.g > 255 || all->color_c.b > 255)
	{
		ft_put_success_or_error("Invalid C\n", 0);
		exit(0);
	}
}

char	*ft_get_path(t_all *all, char **line)
{
	char		*path;
	char		**tmp;

	if (!(tmp = ft_split(*line, ' ')))
	{
		ft_put_success_or_error("Invalid PATH\n", 0);
		//free
		exit(0);
	}
	if (!(path = ft_strdup(tmp[1])) && path[0] != '.' && path[1] != '/')
	{
		ft_put_success_or_error("Invalid PATH\n", 0);
		//free
		exit(0);
	}
	if (tmp[2] != NULL)
	{
		ft_put_success_or_error("Invalid PATH\n", 0);
		//free
		exit(0);
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (path);
}

void	ft_parse_line_r(t_all *all, char **line)
{
	if (all->cubflag.r == 0)
	{
		ft_get_win(all, line);
		DI(all->win_r.x);
		DI(all->win_r.y);
		all->cubflag.r = 1;
	}
	else
	{
		ft_put_success_or_error("Set only one R\n", 1);
		exit(0);
	}
}

void	ft_parse_line_no(t_all *all, char **line)
{
	if (all->cubflag.no == 0)
	{
		all->path_tex.north = ft_get_path(all, line);
		DS(all->path_tex.north);
		all->cubflag.no = 1;
	}
	else
	{
		ft_putstr_fd("Set only one NO\n", 1);
		exit(0);
	}
}

void	ft_parse_line_so(t_all *all, char **line)
{
	if (all->cubflag.so == 0)
	{
		all->path_tex.south = ft_get_path(all, line);
		DS(all->path_tex.south);
		all->cubflag.so = 1;
	}
	else
	{
		ft_putstr_fd("Set only one SO\n", 1);
		exit(0);
	}
}

void	ft_parse_line_we(t_all *all, char **line)
{
	if (all->cubflag.we == 0)
	{
		all->path_tex.west = ft_get_path(all, line);
		DS(all->path_tex.west);
		all->cubflag.we = 1;
	}
	else
	{
		ft_putstr_fd("Set only one WE\n", 1);
		exit(0);
	}
}

void	ft_parse_line_ea(t_all *all, char **line)
{
	if (all->cubflag.ea == 0)
	{
		all->path_tex.east = ft_get_path(all, line);
		DS(all->path_tex.east);
		all->cubflag.ea = 1;
	}
	else
	{
		ft_putstr_fd("Set only one EA\n", 1);
		exit(0);
	}
}

void	ft_parse_line_s(t_all *all, char **line)
{
	if (all->cubflag.s == 0)
	{
		all->path_tex.sprite = ft_get_path(all, line);
		DS(all->path_tex.sprite);
		all->cubflag.s = 1;
	}
	else
	{
		ft_putstr_fd("Set only one S\n", 1);
		exit(0);
	}
}

void	ft_parse_line_f(t_all *all, char **line)
{
	if (all->cubflag.f == 0)
	{
		ft_get_floor(all, line);
		DI(all->color_f.r);
		DI(all->color_f.g);
		DI(all->color_f.b);
		all->cubflag.f = 1;
	}
	else
	{
		ft_putstr_fd("Set only one F\n", 1);
		exit(0);
	}
}

void	ft_parse_line_c(t_all *all, char **line)
{
	if (all->cubflag.c == 0)
	{
		ft_get_ceiling(all, line);
		DI(all->color_c.r);
		DI(all->color_c.g);
		DI(all->color_c.b);
		all->cubflag.c = 1;
	}
	else
	{
		ft_putstr_fd("Set only one C\n", 1);
		exit(0);
	}
}

void	ft_parse_map(t_all *all, char **line)
{
	static int		i = 0;
	int				j;
	int				len;
	static int		numline = 0;

	len = ft_strlen(*line);
	if ((++numline > MAP_HEIGHT - 2) || (len > MAP_WIDTH - 2))
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
	j = 0;
	while ((*line)[j] != '\0')
	{
		if ((*line)[j] == 'N' || (*line)[j] == 'S' || (*line)[j] == 'C' || (*line)[j] == 'S')
		{
			if (all->start_point.flag == 1)
			{
				ft_putstr_fd("Error\n", 1);
				exit(0);
			}
			all->start_point.dir = (*line)[j];
			all->start_point.flag = 1;
			all->start_point.y = i + 1;
			all->start_point.x = j + 1;
			all->map.map[i + 1][j + 1] = 'n';
		}
		else if ((*line)[j] == ' ')
			all->map.map[i + 1][j + 1] = ' ';
		else
			all->map.map[i + 1][j + 1] = (*line)[j];
		j++;
	}
	i++;
}

void	ft_putmap(t_all *all)
{
	int			i;
	int			j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (all->map.map[i][j] == ' ')
            	printf("\x1b[41m%c\x1b[m", all->map.map[i][j]);
			else if (all->map.map[i][j] == 'x')
            	printf("\x1b[34m%c\033[m", all->map.map[i][j]);
			else if (all->map.map[i][j] == 'o')
            	printf("\x1b[35m%c\033[m", all->map.map[i][j]);
			else
            	printf("%c", all->map.map[i][j]);
			j++;
		}
        printf("\n");
		i++;
	}
    printf("\n");
}

int		ft_strchr_ex(char *s, char c)
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
					ft_put_success_or_error("Invalid map", 0);
					exit(0);
				}
			}
			i++;
		}
		return (1);
	}
	return (0);
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
	else if (ft_ismap(all, line))
	{
		all->map.start = 1;
		if (!all->cubflag.r || !all->cubflag.no || !all->cubflag.so
			|| !all->cubflag.we || !all->cubflag.ea
			|| !all->cubflag.s || !all->cubflag.f || !all->cubflag.c)
		{
			ft_put_success_or_error("Failed to read file", 0);
			exit(0);
		}
		ft_parse_map(all, line);
	}
	else if (all->map.start == 1)
	{
		all->map.end = 1;
	}
	else if (ft_check_end_of_file())
	{
		ft_put_success_or_error("Map is not at the end", 0);
		exit(0);
	}
}

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
		ft_put_success_or_error("Failed to read file", 0);
		exit(0);
	}
	ft_parse_line(all, &line);
	free(line);
	ft_putmap(all);
}

void	ft_init_all(t_all *all)
{
	// --save
	all->save = 0;

	// cubflag
	all->cubflag.r = 0;
	all->cubflag.no = 0;
	all->cubflag.so = 0;
	all->cubflag.we = 0;
	all->cubflag.ea = 0;
	all->cubflag.s = 0;
	all->cubflag.f = 0;
	all->cubflag.c = 0;

	// map
	all->map.start = 0;
	all->map.end = 0;

	// window
	all->win_r.x = 0;
	all->win_r.y = 0;

	// path_texture
	all->path_tex.north = NULL;
	all->path_tex.south = NULL;
	all->path_tex.west = NULL;
	all->path_tex.east = NULL;
	all->path_tex.sprite = NULL;

	// start_point
	all->start_point.flag = 0;
}

void	ft_init_map(t_all *all)
{
    int		i;
	int		j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1)
				all->map.map[i][j] = 'x';
			else
				all->map.map[i][j] = ' ';			
			j++;
		}
		i++;
	}
}

void	ft_flood_fill_recursion(t_all *all, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if (x > MAP_WIDTH - 1 || y > MAP_HEIGHT - 1)
		return ;
	if (all->map.map[y][x] != '0' && all->map.map[y][x] != 'n' && all->map.map[y][x] != '1' && all->map.map[y][x] != '2' && all->map.map[y][x] != 'o')
	{
		ft_putmap(all);
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
	if (all->map.map[y][x] != '0' && all->map.map[y][x] != 'n' )
		return ;
	all->map.map[y][x] = 'o';
	ft_flood_fill_recursion(all, x + 1, y);
	ft_flood_fill_recursion(all, x - 1, y);
	ft_flood_fill_recursion(all, x, y + 1);
	ft_flood_fill_recursion(all, x, y - 1);
}

void	ft_flood_fill(t_all *all)
{
	ft_flood_fill_recursion(all, all->start_point.x, all->start_point.y);
	ft_putmap(all);
}


int		ft_iscub(char *cub)
{
	int		len;

	len = ft_strlen(cub);
	if (len > 4 && cub[len - 1] == 'b' && cub[len - 2] == 'u' && cub[len - 3] == 'c' && cub[len - 4] == '.')
		return (1);
	return (0);	
}

int main(int argc, char **argv)
{
	t_all		all;
	int			fd;

	if (((argc == 2 && ft_iscub(argv[1]))) || (argc == 3 && !ft_strncmp(argv[2], "--save", 7)))
	{
		if (argc == 3)
			all.save = 1;
		DI(all.save);
		ft_init_all(&all);
		ft_init_map(&all);
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			ft_put_success_or_error("Failed to open file\n", 0);
			exit(0);
		}
		ft_read_cub(&all, fd);
		ft_flood_fill(&all);
		close(fd);
		ft_put_success_or_error("Start drawing\n", 1);//Success
	}
	else
	{
		ft_put_success_or_error("Comand line arguments are invalid\n", 0);
		ft_putstr_fd("You should do the following:\n", 1);
		ft_putstr_fd("./cub3d *.cub  or  ./cub3d *.cub --save\n", 1);
	}
	return (0);
}