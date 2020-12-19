#include <stdio.h>

void    ft_raycasting2(char **str)
{
    int     i = 0;

    while (i < 5)
    {
        str[i] = '0';
        i++;
    }
}

void    ft_raycasting()
{
    char     str[5];

    ft_raycasting2(str);
    printf("%s\n", str);
}

int main()
{
    ft_raycasting();
}