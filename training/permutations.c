#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i;
	
	i = 0;
    while (str[i] != '\0')
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

void    ft_swap(char *a, char *b)
{
    char tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sorted(char *str)
{
	int		i;
	int		j;

	i = 0;

	while (str[i])
	{
	    j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
			{
				ft_swap(&str[i], &str[j]);
			}
			j++;
		}
		i++;
	}
	return ;
}

void    permutations(char *str, int start, int end)
{
    int i = start;

    if (start == end)
    {
        puts(str);
        return ;
    }
    while (i <= end)
    {
        ft_swap(&str[start], &str[i]);
        sorted(&str[start + i + 1]);
        permutations(str, start + 1, end);
        sorted(&str[start + i + 1]);
        ft_swap(&str[start], &str[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || check_dup(argv[1]))
        return (1);
    int len = ft_strlen(argv[1]) - 1;
    sorted(argv[1]);
    permutations(argv[1], 0, len);
    return (0);
}