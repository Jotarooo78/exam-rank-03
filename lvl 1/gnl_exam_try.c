#include "gnl.h"

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

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int buffer_read = 0;
    char line[70000];
    int i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break ;
        }
        line[i] = buffer[buffer_pos];
        i++;
        buffer_pos++;
        if (line[i - 1] == '\n')
            break ;
    }
    if (i == 0)
        return (NULL);
    line[i] = '\0';
    return (ft_strdup(line));
}

int main(int argc, char **argv)
{
    int fd;
    char *line;

    (void)argc;
    (void)argv;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error");
        return (1);
    }
    line = get_next_line(fd);
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