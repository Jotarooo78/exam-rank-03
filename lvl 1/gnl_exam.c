#include <fcntl.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <stdio.h>    

#define BUFFER_SIZE 1024

char *ft_strdup(char *src)
{
    int i = 0;
    char *dest;

    while (src[i])
        i++;
    dest = (char *)malloc(sizeof(char) * (i + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
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
                break;
        }
        line[i++] = buffer[buffer_pos++];
        if (line[i - 1] == '\n')
            break;
    }

    if (i == 0)
        return (NULL);
    line[i] = '\0';
    return (ft_strdup(line));
}

/*int main(void)
{
    int fd;
    char *str;

    fd = open("test.c", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (1);
    }

    while ((str = get_next_line(fd)) != NULL)
    {
        printf("%s", str);
        free(str);
    }

    close(fd);
    return (0);
}*/