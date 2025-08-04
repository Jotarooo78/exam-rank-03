#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int    ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strdup(char *str)
{
    int i;
    char *dup;

    dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (dup == NULL)
    {
        perror("Error");
        return (NULL);
    }
    i = 0;
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char    *get_stdin(int fd)
{
    static char buffer[1024];
    static int buffer_pos = 0;
    static int buffer_read = 0;
    char line[70000];
    int i = 0;
    
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, 1024);
            if (buffer_read < 0)
            {
                perror("Error");
                buffer_pos = 0;
                buffer_read = 0;
                return (NULL);
            }
        }
        line[i] = buffer[buffer_pos];
        i++;
        buffer_pos++;
        if (line[i - 1] == '\0')
            break ;
    }
    if (i == 0)
        return (NULL);
    line[i] = '\0';
    return (ft_strdup(line));
}

char	*str_filter(char *str, char *filter)
{
    char *new = ft_strdup(str);
    int i = 0;
    int j = 0;

    while (str[i])
    {
        if (str[i] == filter[0])
        {
            j = 1;
            while (j <= ft_strlen(filter))
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
    char *str;
    char *filter;
    char *str_filt;

    if (argc != 2 || argv[1] == NULL)
        return (1);
    str = get_stdin(0);
    if (str == NULL)
        return (1);
    filter = argv[1];
    str_filt = str_filter(str, filter);
    if (str_filt == NULL)
        return (1);
    printf("%s\n", str_filt);
    free(str_filt);
    free(str);
    return (0);
}