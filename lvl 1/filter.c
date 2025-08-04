#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_strdup(char *str)
{
	int	i;
	char	*new;

	i = 0;
	while (str[i])
		++i;
	new = malloc((i + 1) * sizeof(char));
	if (new == NULL)
	{
		perror("Error");
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		++i;
	}
	new[i] = '\0';
	return (new);
}

char	*get_stdin(int fd)
{
	static char	buffer[1024];
	static int	buffer_pos = 0;
	static int	buffer_read = 0;
	char		line[70000];
	int		i = 0;

	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, 1024);
			if (buffer_read == -1)
			{
				perror("Error");
				buffer_pos = 0;
				buffer_read = 0;
				return (NULL);
			}
			buffer_pos = 0;
			if (buffer_read == 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
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
					break;
				++j;
			}
			if (j == ft_strlen(filter))
			{
				j = 0;
				while (filter[j])
				{
					new[i] = '*';
					++i;
					++j;
				}
				--i;
			}
		}
		++i;
	}
	return (new);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || argv[1] == NULL)
		return (1);
	char 	*str;
	str = get_stdin(0);
	if (str == NULL)
		return (1);
	char	*filter = argv[1];
	char	*fstr;
	fstr = str_filter(str, filter);
	if (fstr == NULL)
		return (1);
	printf("%s", fstr);
	free(str);
	free(fstr);
	return (0);
}