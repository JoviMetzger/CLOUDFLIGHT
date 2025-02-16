#include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		len;
	int		i;
	char	*dup;

	len = ft_strlen(str);
	i = -1;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	char	buffer;
	char	rtn[7000000];
	int		n;
	int		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	n = read(fd, &buffer, 1);
	while (n > 0)
	{
		rtn[i++] = buffer;
		if (buffer == '\n')
			break ;
		n = read(fd, &buffer, 1);
	}
	rtn[i] = '\0';
	if (n <= 0 && i == 0)
		return (NULL);
	return (ft_strdup(rtn));
}

void sorting(char *s, FILE *output)
{
    int i = 0;

    if (s[i] == s[i+1])
        fputs(&s[i+1], output);
    if ((s[i] == 'S' && s[i+1] == 'P') || (s[i] == 'P' && s[i+1] == 'S'))
        fputs("S\n", output);
    if ((s[i] == 'S' && s[i+1] == 'R') || (s[i] == 'R' && s[i+1] == 'S'))
        fputs("R\n", output);
    if ((s[i] == 'P' && s[i+1] == 'R') || (s[i] == 'R' && s[i+1] == 'P'))
        fputs("P\n", output);
}


int main (void)
{
    int fd1 = open("level1_1.in", O_RDONLY);
    // int fd2 = open("level1_2.in", O_RDONLY);
    // int fd3 = open("level1_3.in", O_RDONLY);
    // int fd4 = open("level1_4.in", O_RDONLY);
    // int fd5 = open("level1_5.in", O_RDONLY);
    int i = 0;

    FILE *output_file = fopen("output1_1.txt", "w+");

    while (1)
	{
		char *line = get_next_line(fd1);
        // char *line = get_next_line(fd2);
        // char *line = get_next_line(fd3);
        // char *line = get_next_line(fd4);
        // char *line = get_next_line(fd5);
		if (line == NULL)
			break ;
        sorting(line, output_file);
	}
	close (fd1);
	return (0);
}
