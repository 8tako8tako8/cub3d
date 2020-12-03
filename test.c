#include <stdio.h>
#include <math.h>
# define numSprites 10

typedef	struct	s_sprite
{
	double		x;
	double		y;

}				t_sprite;

double  ft_decimals(double value)
{
    double  ret_decimals;

    ret_decimals = value - (int)value;
    return ret_decimals;
}

double  ft_floor(double value)
{
    double  ret_int;

    if (value < 0)
    {
        if (value < value - ft_decimals(value))
            ret_int = value - ft_decimals(value) - 1;
        else
            ret_int = (int)value;
    }
    else
        ret_int = (int)value;
    return (ret_int);
}

int main()
{
    double  i = 3.14;
    double  j = -3.00;

    printf("%f, %f\n", floor(i), ft_floor(i));
    printf("%f, %f\n", floor(j), ft_floor(j));

/*     t_sprite    sprite[numSprites];
    int         i = 0;

    while (i < 3)
    {
        if (i == 0)
        {
            sprite[i].x = 2.0;
            sprite[i].y = 1.0;
        }
        else
        {
            sprite[i].x = 1.0;
            sprite[i].y = 1.0;
        }
        i++;
    }
    i = 0;
    while (i < 3)
    {
        printf("x: %f, y: %f\n", sprite[i].x, sprite[i].y);
        i++;
    } */
    return 0;
}