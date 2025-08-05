#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int check_dup(char *str)
{
    int i = 0;
    int j;
    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] == str[j])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

void    sorted(char *str)
{
    int i = 0;
    int j;
    char tmp;

    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
            {
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    generate(char *str, char *result, int *used, int len, int depth)
{
    int i = 0;
    if (depth == len)
    {
        write(1, result, len);
        write(1, "\n", 1);
    }
    while (i < len)
    {
        if (!used[i])
        {
            used[i] = 1;
            result[depth] = str[i];
            generate(str, result, used, len, depth + 1);
            used[i] = 0;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || check_dup(argv[1]))
        return (1);
    int len = ft_strlen(argv[1]);
    char *result;
    int *used;
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (1);
    used = calloc(len, 0);
    if (!used)
        return (1);
    sorted(argv[1]);
    generate(argv[1], result, used, len, 0);
    return (0);
}