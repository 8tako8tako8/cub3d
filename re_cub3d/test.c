#include <stdio.h>
#include <stdlib.h>

void    reverse_map_to_y(int **map, int **map_2)
{
    int     i;
    int     j;
    int     max_i = 5;
    int     max_j = 5;

    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            map_2[i][j] = map[max_i - i - 1][j];
            j++;
        }
        i++;
    }
}

int main()
{
    int     i;
    int     j;
    int     **map;
    int     **map_2;

    map_2 = NULL;
    map = (int **)malloc(sizeof(int *) * 5);
    i = 0;
    while (i < 5)
    {
        map[i] = (int *)malloc(sizeof(int) * 5);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            map[i][j] = 0;
            j++;
        }
        i++;
    }

    map[0][0] = 1;
    map[0][4] = 2;
    map[4][0] = 3;
    map[4][4] = 4;

    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            printf("%d",map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    map_2 = (int **)malloc(sizeof(int *) * 5);
    i = 0;
    while (i < 5)
    {
        map_2[i] = (int *)malloc(sizeof(int) * 5);
        i++;
    }

    reverse_map_to_y(map, map_2);

    printf("\n");

    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            printf("%d",map_2[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}