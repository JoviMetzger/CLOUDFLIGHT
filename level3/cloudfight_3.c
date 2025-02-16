#include <stdio.h>
#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include <ctype.h>

// typedef struct s_stack
// {
// 	int content;
// 	int	index;
// 	struct s_stack	*next;
// } t_list;

// typedef struct s_data
// {
// 	t_list *stack_p;
// 	t_list *stack_r;
// 	t_list *stack_s;  
// } t_data;

// t_list	*new_node(char *str_input)
// {
// 	t_list	*new_node;

// 	new_node = malloc(sizeof (t_list));
// 	if (new_node == NULL)
// 		terminate(1);
// 	new_node->value = ft_atoi(str_input);
// 	new_node->index = -1;
// 	new_node->next = NULL;
// 	new_node->previous = NULL;
// 	return (new_node);
// }

// t_list	*lstlast(t_list *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void	lstadd_back(t_list **list, t_list *new)
// {
// 	t_list	*back;

// 	if (*list)
// 	{
// 		back = lstlast(*list);
// 		back->next = new;
// 		new->previous = back;
// 	}
// 	else
// 		*list = new;
// }

// void	lstadd_front(t_list **lst, t_list *new)
// {
// 	new->next = *lst;
// 	*lst = new;
// }

// int	list_length(t_list *list)
// {
// 	int	i;

// 	i = 0;
// 	while (list)
// 	{
// 		list = list->next;
// 		i++;
// 	}
// 	return (i);
// }

static int	lencount(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

static int	wordcount(char const *s, char c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			word++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_str;
	size_t		l;

	l = strlen((char *)s);
	if (start >= l)
		len = 0;
	else if (len > l - start)
		len = l - start;
	new_str = (char *)malloc((sizeof(char) * (len + 1)));
	if (new_str == NULL)
		return (NULL);
	if (l == 0 || len == 0)
		new_str[0] = 0;
	else
		strlcpy(new_str, &s[start], len + 1);
	return (new_str);
}

static char	**freedom(char **md_array)
{
	int	i;

	i = 0;
	while (md_array[i] != NULL)
	{
		free(md_array[i]);
		i++;
	}
	free(md_array);
	return (NULL);
}

static char	*fill(char const *s, char c, int *i)
{
	char	*str;
	char	*d;
	int		len;

	d = (char *)s;
	len = lencount(d, c);
	str = ft_substr(d, 0, len);
	if (str == 0)
	{
		return (0);
	}
	*i += len;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	split_str = (char **)malloc((sizeof(char *) * (wordcount(s, c) + 1)));
	if (split_str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		split_str[j] = fill(&s[i], c, &i);
		if (split_str[j] == NULL)
			return (freedom(split_str));
			j++;
	}
	split_str[j] = NULL;
	return (split_str);
}

static	int	ft_iswhitespace(char c)
{
	return (c == ' ' || ((c >= 9 && c <= 13)));
}

long int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	number = 0;
	sign = 1;
	i = 0;
	while (ft_iswhitespace(str[i]) && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (isdigit(str[i]))
	{
		number = number * 10 + str[i] -48;
		i++;
	}
	return (number * sign);
}

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



void converting(char *line)
{
    char **arr = ft_split(line, ' ');
    int i = strlen(arr[0])-1;
    char *new = ft_substr(arr[0], 0, i);
    printf("%s\n", new);
//     atoi(new);
//  atoi string;
//  firts is always R, sedcond always P, third always S
//  atoi string
}

int main (void)
{
    int fd1 = open("level3_1.in", O_RDONLY);
    // int fd2 = open("level2_2.in", O_RDONLY);
    // int fd3 = open("level2_3.in", O_RDONLY);
    // int fd4 = open("level2_4.in", O_RDONLY);
    // int fd5 = open("level3_1.in", O_RDONLY);
    int i = 0;

    FILE *output_file = fopen("output3_1.txt", "w+");
    char *line = get_next_line(fd1);
    while (1)
	{
		line = get_next_line(fd1);
        // char *line = get_next_line(fd2);
        // char *line = get_next_line(fd3);
        // char *line = get_next_line(fd4);
        // char *line = get_next_line(fd5);
		if (line == NULL)
			break ;
        converting(line);
        fputc('\n', output_file);
	}
	close (fd1);
    exit(0);
	return (0);
}