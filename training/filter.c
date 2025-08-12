#include "gnl.h"

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

char    *ft_strdup(char *str)
{
    char *dup;
    int i;

    dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char    *get_next_line(int fd)
{
    static char buffer[1024];
    static int buffer_pos = 0;
    static int buffer_read = 0;
    char line[50000];
    int i = 0;

    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, 1024);
            if (buffer_read == -1)
            {
                buffer_pos = 0;
                buffer_read = 0;
                return (NULL); // 2 seuls fois de return NULL
            }
            if (buffer_read == 0) // dans le grand if, pas dans le while + le sign == pas <=
                break ;
            buffer_pos = 0;
        }
        line[i] = buffer[buffer_pos];
        i++;
        buffer_pos++;
        if (line[i - 1] == '\0')
            break ; 
    }
    if (i == 0)
        return (NULL);
    line[i] = '\0'; // a ne pas oublier le '\0'
    return (ft_strdup(line));
}

char    *str_filter(char *str, char *filter)
{
    int i = 0;
    int j;
    char *new;

    new = ft_strdup(str);
    while (str[i])
    {
        j = 0;
        if (str[i] == filter[0])
        {
            while (j < ft_strlen(filter))
            {
                if (str[i + j] != filter[j])
                    break ;
                j++;
            }
            if (j == ft_strlen(filter))
            {
                j = 0;
                while (filter[j])
                {
                    new[i] = '*';
                    i++;
                    j++;
                }
                i--;
            }
        }
        i++;
    }
    return (new);
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1] == NULL)
        return (1);
    char *filter;
    char *str_filt;
    char *str;
    str = get_next_line(0);
    if (!str)
        return (1);
    filter = (argv[1]);
    str_filt = str_filter(str, filter);
    if (str_filt == NULL)
        return (1);
    printf("%s", str_filt);
    free(str); // ne pas oublier de free
    free(str_filt);
    return (0);
}