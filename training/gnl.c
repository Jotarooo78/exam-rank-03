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
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_pos = 0;
    static int buffer_read = 0;
    char line[100000];
    int i = 0;

    if (BUFFER_SIZE <= 0 || fd < 0) // 3 seuls NULL
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            if (buffer_read <= 0)
                break ;
            buffer_pos = 0;
        }
        line[i] = buffer[buffer_pos];
        i++;
        buffer_pos++;
        if (line[i - 1] == '\n') // pas oublier la difference
            break ; 
    }
    if (i == 0)
        return (NULL);
    line[i] = '\0';
    return (ft_strdup(line));
}

int main(int argc, char **argv)
{
    (void)argc;

    int fd;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (1);
    char *line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return (0);
}