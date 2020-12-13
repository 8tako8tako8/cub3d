#include <stdio.h>
#include <math.h>

typedef struct  s_all
{
    int         r;
    int         g;
    int         b;
    int         hex;
}               t_all;

void	print_dx_num(long dx, int base)
{
	if (dx < base)
	{
		write(1, number + dx, 1);
	}
	else
	{
		print_dx_num(dx / base, base);
		print_dx_num(dx % base, base);
	}
}

void    ft_convert_hex(t_all *all)
{
    char    number[] = "0123456789BCDEF";
    char    *hex_num;

    hex_num = (char *)malloc(9);
    hex_num[8] = '\0';
    printf

}

int main()
{
    t_all   all;

    all.r = 10;
    all.g = 100;
    all.b = 255;
    ft_convert_hex(&all);

    return 0;
}