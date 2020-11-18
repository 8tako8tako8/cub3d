#include "cub3d.h"

void	ft_get_win(t_all *all, char **line)
{
	int		i;

	i = 2;
	all->win.x = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ' ')
		i++;
	all->win.y = ft_atoi(*line + i);
}

void	ft_get_color(t_all *all, char **line)
{
	int		i;

	i = 2;
	all->floor.r = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->floor.g = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->floor.b = ft_atoi(*line + i);
}

void	ft_get_ceiling(t_all *all, char **line)
{
	int		i;

	i = 2;
	all->ceiling.r = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->ceiling.g = ft_atoi(*line + i);
	while (ft_isdigit((*line)[i]))
		i++;
	if ((*line)[i] == ',')
		i++;
	all->ceiling.b = ft_atoi(*line + i);
}

char	*ft_get_path(t_all *all, char **line)
{
	char		*path;
	char		**tmp;

	if (!(tmp = ft_split(*line, ' ')))
	{
		ft_putstr_fd("Error\n", 1);
		//free
		exit(0);
	}
	if (!(path = ft_strdup(tmp[1])) && path[0] != '.' && path[1] != '/')
	{
		ft_putstr_fd("Error\n", 1);
		//free
		exit(0);
	}
	if (tmp[2] != NULL)
	{
		ft_putstr_fd("Error\nWrong .cub", 1);
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
		DI(all->win.x);
		DI(all->win.y);
		all->cubflag.r = 1;
	}
	else
	{
		ft_putstr_fd("Error\n", 1);
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
		ft_putstr_fd("Error\n", 1);
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
		ft_putstr_fd("Error\n", 1);
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
		ft_putstr_fd("Error\n", 1);
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
		ft_putstr_fd("Error\n", 1);
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
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
}

void	ft_parse_line_f(t_all *all, char **line)
{
	if (all->cubflag.f == 0)
	{
		ft_get_color(all, line);
		DI(all->floor.r);
		DI(all->floor.g);
		DI(all->floor.b);
		all->cubflag.f = 1;
	}
	else
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
}

void	ft_parse_line_c(t_all *all, char **line)
{
	if (all->cubflag.c == 0)
	{
		ft_get_ceiling(all, line);
		DI(all->ceiling.r);
		DI(all->ceiling.g);
		DI(all->ceiling.b);
		all->cubflag.c = 1;
	}
	else
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
}

/* void	ft_init_map(t_all *all, char **line)
{
	int		i;
	int		j;

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			if (i == 0 || i == 499 || j == 0 || j == 499)
				all->map.map[i][j] = 'x';
			else
				all->map.map[i][j] = 'p';			
			j++;
		}
		i++;
	}
} */

void	ft_parse_map(t_all *all, char **line)
{
	static int		i = 0;
	int				j;
	int				len;
	static int		numline = 0;

	len = ft_strlen(*line);
	if ((++numline > MAP_SIZE_Y - 2) || (len > MAP_SIZE_X - 2))
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
	j = 0;
	while ((*line)[j] != '\0')
	{
		if ((*line)[j] == 'N' || (*line)[j] == 'S' || (*line)[j] == 'C' || (*line)[j] == 'S')
		{
			if (all->posi.posiflag == 1)
			{
				ft_putstr_fd("Error\n", 1);
				exit(0);
			}
			all->posi.dir = (*line)[j];
			all->posi.posiflag = 1;
			all->posi.posix = i + 1;
			all->posi.posiy = j + 1;
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
	while (i < MAP_SIZE_Y)
	{
		j = 0;
		while (j < MAP_SIZE_X)
		{
			if (all->map.map[i][j] == ' ')
            	printf("\x1b[41m%c\x1b[m", all->map.map[i][j]);
			else if (all->map.map[i][j] == 'x')
            	printf("\x1b[34m%c\033[m", all->map.map[i][j]);
			else
            	printf("%c", all->map.map[i][j]);
			j++;
		}
        printf("\n");
		i++;
	}

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
	//chack必要
	//ft_ismap
	if  ((*line)[0] == '0' || (*line)[0] == '1' || (*line)[0] == '2' || (*line)[0] == ' ')
		ft_parse_map(all, line);
}

void	ft_read_map(t_all *all, int fd)
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
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
	ft_parse_line(all, &line);
	free(line);
	ft_putmap(all);
}

void	ft_init_all(t_all *all)
{
	// cubflag
	all->cubflag.r = 0;
	all->cubflag.no = 0;
	all->cubflag.so = 0;
	all->cubflag.we = 0;
	all->cubflag.ea = 0;
	all->cubflag.s = 0;
	all->cubflag.f = 0;
	all->cubflag.c = 0;

	// window
	all->win.x = 0;
	all->win.y = 0;

	// path_texture
	all->path_tex.north = NULL;
	all->path_tex.south = NULL;
	all->path_tex.west = NULL;
	all->path_tex.east = NULL;
	all->path_tex.sprite = NULL;

	// position
	all->posi.posiflag = 0;
}

void	ft_init_map(t_all *all)
{
    int		i;
	int		j;

	i = 0;
	while (i < MAP_SIZE_Y)
	{
		j = 0;
		while (j < MAP_SIZE_X)
		{
			if (i == 0 || i == MAP_SIZE_Y - 1 || j == 0 || j == MAP_SIZE_X - 1)
				all->map.map[i][j] = 'x';
			else
				all->map.map[i][j] = ' ';			
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_all		all;
	int			fd;

	if (argc > 3 || argc == 1)
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
	ft_init_all(&all);
	ft_init_map(&all);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
	}
	ft_read_map(&all, fd);
	close(fd);
	return (0);
}
