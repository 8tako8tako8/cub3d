#include <unistd.h>

void    ft_putred(char *s)
{
    int     i = 0;

    write(1, "\e[31m", 5);
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    write(1, "\n\e[m", 4);
}

int main()
{
    ft_putred("abcdef");

    return 0;
}