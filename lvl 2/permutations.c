#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i;
	
	i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void sorted(char *str)
{
	char 	tmp;
	int		i;
	int		j;

	i = 0;
	j = i + 1;

	while (str[i] != '\0')
	{
		while (str[j] != '\0')
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
	return ;
}


void    permutations(char *str, char *result, int *used, int len, int depth)
{
    int i = 0;
    if (depth == len)
    {
        puts(result);
        return ;
    }
    while (i < len)
    {
        if (!used[i])
        {
            used[i] = 1;
            result[depth] = str[i];
            permutations(str, result, used, len, depth + 1);
            used[i] = 0;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    int len = ft_strlen(argv[1]);
    char *result = malloc(sizeof(char) * (len + 1));
    int *used = calloc(len, sizeof(int));
    if (!used || !result)
        return (1);
    sorted(argv[1]);
    permutations(argv[1], result, used, len, 0);
    free(result);
    free(used);
    return (0);
}