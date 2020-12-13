#include <stdio.h>
#include <stdlib.h>

typedef struct  s_info
{
    int         x;
    int         y;
    int         **buf;
    int         **texture;
    int         height[5];
    int         width[5];
}               t_info;

typedef struct  s_all
{
    t_info      info;    
}               t_all;

void	ft_init_win_and_tex(t_all *all)
{
	int		i;
	int		j;

	all->info.texture = (int **)malloc(sizeof(int *) * 5);
	i = 0;
	while (i < 5)
	{
		all->info.texture[i] = (int *)malloc(sizeof(int) * (all->info.height[i] * all->info.width[i]));
		i++;
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < all->info.height[i] * all->info.width[i])
			all->info.texture[i][j++] = 0;
		i++;
	}
}

int main()
{
    t_all   all;

    all.info.height[0]=64;
    all.info.height[1]=64;
    all.info.height[2]=64;
    all.info.height[3]=64;
    all.info.height[4]=64;
    all.info.width[0]=64;
    all.info.width[1]=64;
    all.info.width[2]=64;
    all.info.width[3]=64;
    all.info.width[4]=64;
    ft_init_win_and_tex(&all);
}