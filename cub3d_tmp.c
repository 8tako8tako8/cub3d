/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:50:57 by kmorimot          #+#    #+#             */
/*   Updated: 2020/12/21 22:44:01 by kmorimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	ft_print_map(t_all *all)
{
	int		i, j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (all->map.map[i][j] == 0)
				printf("\x1b[41m%d\x1b[m", all->map.map[i][j]);
			else
				printf("%d", all->map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
} */

/* void	ft_putmap(t_all *all)
{
	int			i;
	int			j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (all->map.charmap[i][j] == ' ')
            	printf("\x1b[41m%c\x1b[m", all->map.charmap[i][j]);
			else if (all->map.charmap[i][j] == 'x')
            	printf("\x1b[34m%c\033[m", all->map.charmap[i][j]);
			else if (all->map.charmap[i][j] == 'o')
            	printf("\x1b[35m%c\033[m", all->map.charmap[i][j]);
			else
            	printf("%c", all->map.charmap[i][j]);
			j++;
		}
        printf("\n");
		i++;
	}
    printf("\n");
} */

//----------------put error --------------------

/* void	ft_put_success_or_error(char *s, int fd)
{
	if (fd == 2)
	{
		write(1, "\e[31mError\e[m\n", 15);
		ft_putstr_fd(s, fd);
	}
	else if (fd == 1)
	{
		write(1, "\e[32mSuccess\e[m\n", 17);
		ft_putstr_fd(s, fd);
	}
} */



//----------------put error --------------------

//-------------------- utils -----------------------------------

/* int		ft_isspace(char c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int		ft_isonlyspace(char **line)
{
	int		i;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if (!ft_isspace((*line)[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_combine_color(t_all *all)
{
	all->color_f.rgb = all->color_f.r * 65536 + all->color_f.g * 256 + all->color_f.b;
	all->color_c.rgb = all->color_c.r * 65536 + all->color_c.g * 256 + all->color_c.b;
} */

//-------------------- utils -----------------------------------

//----------------- libft ------------------------------

/* static int	check_int_overflow(int sign, const char *str)
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

int		ft_atoi_ex(const char *str)
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

void		ft_lstclear_ex(t_sprlst **lst)
{
	t_sprlst	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if (*lst)
			free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_sprlst	*ft_newspr(double x, double y)
{
	t_sprlst	*newlist;

	if (!(newlist = (t_sprlst *)malloc(sizeof(t_sprlst))))
		return (NULL);
	newlist->x = x;
	newlist->y = y;
	newlist->next = NULL;
	return (newlist);
}

t_sprlst		*ft_lstlast_ex(t_sprlst *lst)
{
	t_sprlst	*curr_list;

	if (lst == NULL)
		return (NULL);
	curr_list = lst;
	while (curr_list->next != NULL)
		curr_list = curr_list->next;
	return (curr_list);
}

void	ft_lstadd_back_ex(t_sprlst **lst, t_sprlst *new)
{
	t_sprlst		*curr_lst;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_lst = ft_lstlast_ex(*lst);
	curr_lst->next = new;
}

int			ft_lstsize_ex(t_sprlst *lst)
{
	t_sprlst	*curr_lst;
	int			i;

	if (lst == NULL)
		return (0);
	curr_lst = lst;
	i = 1;
	while (curr_lst->next != NULL)
	{
		curr_lst = curr_lst->next;
		i++;
	}
	return (i);
} */

//----------------- libft ------------------------------

//------------- flood fill -----------------------------

/* void	ft_convert_map_char_to_int(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (all->map.charmap[i][j] == 'o')
				all->map.map[i][j] = 0;
			else if (all->map.charmap[i][j] == '@')
				all->map.map[i][j] = 2;
			else
				all->map.map[i][j] = 1;
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
	if (all->map.charmap[y][x] == ' ')
		ft_put_error_and_exit("There is space in the walking range\n", all);
	if (all->map.charmap[y][x] != '0' && all->map.charmap[y][x] != 'n' && all->map.charmap[y][x] != '1' 
	&& all->map.charmap[y][x] != '2' && all->map.charmap[y][x] != 'o' && all->map.charmap[y][x] != '@')
		ft_put_error_and_exit("Map is not closed\n", all);
	if (all->map.charmap[y][x] != '0' && all->map.charmap[y][x] != 'n' && all->map.charmap[y][x] != '2')
		return ;
	if (all->map.charmap[y][x] == '2')
		all->map.charmap[y][x] = '@';
	else
		all->map.charmap[y][x] = 'o';
	ft_flood_fill_recursion(all, x + 1, y);
	ft_flood_fill_recursion(all, x - 1, y);
	ft_flood_fill_recursion(all, x, y + 1);
	ft_flood_fill_recursion(all, x, y - 1);
}

void	ft_flood_fill(t_all *all)
{
	ft_flood_fill_recursion(all, all->start_point.x, all->start_point.y);
//	ft_putmap(all);
	ft_convert_map_char_to_int(all);
} */

//------------- flood fill -----------------------------

//------------- cub utils ------------------------------

/* void	ft_skip_digit(char **line, int *i, int *count)
{
	if (ft_isdigit((*line)[*i]))
		(*count)++;
	while (ft_isdigit((*line)[*i]))
		(*i)++;
}

void	ft_get_win(t_all *all, char **line)
{
	int		i;

	i = 2;
	all->win_r.x = ft_atoi_ex(*line + i);
	while ((*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		i++;
	all->win_r.y = ft_atoi_ex(*line + i);
	while ((*line)[i] == ' ')
		i++;
	while (ft_isdigit((*line)[i]))
		i++;
	while ((*line)[i] == ' ')
		i++;
	if ((*line)[i] || all->win_r.x <= 0 || all->win_r.y <= 0)
	{
		ft_put_error_and_exit("Invalid R\n", all);		
	}
}

void	ft_get_floor(t_all *all, char **line)
{
	int		count;
	int		i;

	count = 0;
	i = 2;
	all->color_f.r = ft_atoi_ex(*line + i);
	while ((*line)[i] == ' ')
		i++;
	ft_skip_digit(line, &i, &count);
	if ((*line)[i] == ',')
		i++;
	all->color_f.g = ft_atoi_ex(*line + i);
	ft_skip_digit(line, &i, &count);
	if ((*line)[i] == ',')
		i++;
	all->color_f.b = ft_atoi_ex(*line + i);
	ft_skip_digit(line, &i, &count);
	while ((*line)[i] == ' ')
		i++;
	if (count != 3 || (*line)[i] || all->color_f.r < 0 || all->color_f.g < 0 || all->color_f.b < 0
							|| all->color_f.r > 255 || all->color_f.g > 255 || all->color_f.b > 255)
		ft_put_error_and_exit("Invalid F\n", all);
}

void	ft_get_ceiling(t_all *all, char **line)
{
	int		count;
	int		i;

	count = 0;
	i = 2;
	all->color_c.r = ft_atoi_ex(*line + i);
	while ((*line)[i] == ' ')
		i++;
	ft_skip_digit(line, &i, &count);
	if ((*line)[i] == ',')
		i++;
	all->color_c.g = ft_atoi_ex(*line + i);
	ft_skip_digit(line, &i, &count);
	if ((*line)[i] == ',')
		i++;
	all->color_c.b = ft_atoi_ex(*line + i);
	ft_skip_digit(line, &i, &count);
	while ((*line)[i] == ' ')
		i++;
	if (count != 3 || (*line)[i] || all->color_c.r < 0 || all->color_c.g < 0 || all->color_c.b < 0
		|| all->color_c.r > 255 || all->color_c.g > 255 || all->color_c.b > 255)
		ft_put_error_and_exit("Invalid C\n", all);
}

char	*ft_get_path(char **line, t_all *all)
{
	char		*path;
	char		**tmp;
	int			i;

	i = 2;
	while ((('\t' <= (*line)[i]) && ((*line)[i] <= '\r')) || ((*line)[i] == ' '))
		i++;
	if (!((*line)[i]))
		ft_put_error_and_exit("There is no PATH\n", all);
	if (!(tmp = ft_split(*line, ' ')))
		ft_put_error_and_exit("Invalid PATH\n", all);
	if (!(path = ft_strdup(tmp[1])) || !(path[0] == '.' && path[1] == '/'))
	{
		if (path)
			free(path);
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
} */

//------------- cub utils ------------------------------

//-------------------- R -----------------------------------

/* void	ft_parse_line_r(t_all *all, char **line)
{
	if (all->cubflag.r == 0)
	{
		ft_get_win(all, line);
		all->cubflag.r = 1;
	}
	else
	{
		ft_put_error_and_exit("Set only one R\n", all);
	}
}

void	ft_parse_line_no(t_all *all, char **line)
{
	if (all->cubflag.no == 0)
	{
		all->path_tex.north = ft_get_path(line, all);
		all->cubflag.no = 1;
	}
	else
	{
		ft_put_error_and_exit("Set only one NO\n", all);
	}
}

void	ft_parse_line_so(t_all *all, char **line)
{
	if (all->cubflag.so == 0)
	{
		all->path_tex.south = ft_get_path(line, all);
		all->cubflag.so = 1;
	}
	else
	{
		ft_put_error_and_exit("Set only one SO\n", all);
	}
}

void	ft_parse_line_we(t_all *all, char **line)
{
	if (all->cubflag.we == 0)
	{
		all->path_tex.west = ft_get_path(line, all);
		all->cubflag.we = 1;
	}
	else
	{
		ft_put_error_and_exit("Set only one WE\n", all);
	}
}

void	ft_parse_line_ea(t_all *all, char **line)
{
	if (all->cubflag.ea == 0)
	{
		all->path_tex.east = ft_get_path(line, all);
		all->cubflag.ea = 1;
	}
	else
	{
		ft_put_error_and_exit("Set only one EA\n", all);
	}
}

void	ft_parse_line_s(t_all *all, char **line)
{
	if (all->cubflag.s == 0)
	{
		all->path_tex.sprite = ft_get_path(line, all);
		all->cubflag.s = 1;
	}
	else
	{
		ft_put_error_and_exit("Set only one S\n", all);
	}
}

void	ft_parse_line_f(t_all *all, char **line)
{
	if (all->cubflag.f == 0)
	{
		ft_get_floor(all, line);
		all->cubflag.f = 1;
	}
	else
		ft_put_error_and_exit("Set only one F\n", all);
}

void	ft_parse_line_c(t_all *all, char **line)
{
	if (all->cubflag.c == 0)
	{
		ft_get_ceiling(all, line);
		all->cubflag.c = 1;
	}
	else
		ft_put_error_and_exit("Set only one C\n", all);
} */

//-------------------- C -----------------------------------

//-------------------- parse map -----------------------------------

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
	int				len;
	static int		numline = 0;

	len = ft_strlen(*line);
	if ((++numline > MAP_HEIGHT - 2) || (len > MAP_WIDTH - 2))
	{
		ft_put_error_and_exit("Map size limit is exceeded\n", all);
	}
	j = 0;
	while ((*line)[j] != '\0')
	{
		if ((*line)[j] == 'N' || (*line)[j] == 'S' || (*line)[j] == 'W' || (*line)[j] == 'E')
			ft_set_start_point(all, line, &i, &j);
		else if ((*line)[j] == '2')
		{
			ft_lstadd_back_ex(&(all->sprlst), ft_newspr(j + 1.5, i + 1.5));
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

//-------------------- parse map -----------------------------------

//-------------------- read cub -----------------------------------

/* int		ft_check_after_map(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (-1);
		i++;
	}
	return (1);
}

void	ft_check_element_and_parse_map(t_all *all, char **line)
{
	all->map.start = 1;
	if (all->map.end == 1)
		ft_put_error_and_exit("Invalid map\n", all);
	if (!all->cubflag.r || !all->cubflag.no || !all->cubflag.so
		|| !all->cubflag.we || !all->cubflag.ea
		|| !all->cubflag.s || !all->cubflag.f || !all->cubflag.c)
		ft_put_error_and_exit("All elements are needed (R,NO,SO,WE,EA,S,F,C)\n", all);
	ft_parse_map(all, line);
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
	else if (ft_ismap(all, *line))
		ft_check_element_and_parse_map(all, line);
	else if (all->map.start == 1 && all->map.end == 0)
		all->map.end = 1;
	else if (all->map.start == 1 && all->map.end == 1 && ft_check_after_map(*line) == -1)
		ft_put_error_and_exit("Map is not at the end\n", all);
	else if (!ft_isonlyspace(line))
		ft_put_error_and_exit("Neither element nor map\n", all);
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
		ft_put_error_and_exit("Failed to read file\n", all);
	}
	ft_parse_line(all, &line);
	free(line);
	ft_combine_color(all);
//	ft_putmap(all);
} */

//-------------------- read cub -----------------------------------

//-------------------- init -----------------------------------

void	ft_init_sprite(t_all *all)
{
	all->spr.num = ft_lstsize_ex(all->sprlst);
	all->spr.sprite_x = (double *)malloc(sizeof(double) * all->spr.num);
	all->spr.sprite_y = (double *)malloc(sizeof(double) * all->spr.num);
}

void	ft_init_all(t_all *all, int argc)
{
	all->save = 0;
	if (argc == 3)
		all->save = 1;
	all->cubflag.r = 0;
	all->cubflag.no = 0;
	all->cubflag.so = 0;
	all->cubflag.we = 0;
	all->cubflag.ea = 0;
	all->cubflag.s = 0;
	all->cubflag.f = 0;
	all->cubflag.c = 0;
	all->map.start = 0;
	all->map.end = 0;
	all->sprlst = NULL;
	all->win_r.x = 0;
	all->win_r.y = 0;
	all->start_point.flag = 0;
	all->player.speed = 0.01;
	all->player.rotspeed = 0.01;
	all->key.key_a = 0;
	all->key.key_w = 0;
	all->key.key_s = 0;
	all->key.key_d = 0;
	all->key.key_esc = 0;
	all->key.key_left = 0;
	all->key.key_right = 0;
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
				all->map.charmap[i][j] = 'x';
			else
				all->map.charmap[i][j] = '4';			
			j++;
		}
		i++;
	}
}

void	ft_init(t_all *all, int argc)
{
	ft_init_all(all, argc);
	ft_init_map(all);
}

//-------------------- init -----------------------------------

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
		mlx_hook(all.mlx.win, 2, 1L<<0, &ft_press_key, &all);
		mlx_hook(all.mlx.win, 3, 1L<<1, &ft_release_key, &all);
		mlx_hook(all.mlx.win, 17, 1L<<17, &ft_exit, &all);
		mlx_loop(all.mlx.mlx);
	}
	else
		ft_put_error_and_exit("Invalid arguments\n./cub3d *.cub or ./cub3d *.cub --save\n", &all);
}
