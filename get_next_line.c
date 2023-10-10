/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:30:41 by mllamas-          #+#    #+#             */
/*   Updated: 2023/10/09 13:30:44 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
 #include <fcntl.h>

size_t	ft_strlen(char *s)
{
	size_t	a;

	a = 0;
	while (*s)
	{
		a++;
		s++;
	}
	return (a);
}

static void	*ft_calloc(size_t count, size_t size)
{
	void			*b;
	unsigned char	*ptr;
	size_t			i;

	i = count * size;
	b = malloc(i);
	if (!b)
		return (b);
	ptr = b;
	while (i > 0)
	{
		ptr[i - 1] = 0;
		i--;
	}
	return ((void *)ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (str);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = (char)s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

static int check_buffer(char *buffer)
{
    while (buffer)
    {
        if (*buffer == '\n')
            return (1);
        buffer++;
    }
    return (0);
}

static char *get_buffer(int fd)
{
    char    *buffer;
    int     i;

    i = 1;
    buffer = malloc(BUFFER_SIZE);
    if (!buffer)
        return(NULL);
    if (read(fd, buffer, BUFFER_SIZE) < 0)
        return (NULL);
    return (buffer);
}

char    *get_next_line(int fd)
{
    char    *line;
    char    *a;

    line = get_buffer(fd);
    a = get_buffer(fd);
    line = ft_strjoin(line, a); 
    return (line);
}
//    line = ft_left(line);
//    return(ft_final_line(line));

int main(void)
{
    int fd;
    char    *a;

    fd = open("prueba.txt", O_RDONLY);
    a = get_next_line(fd);
    printf("%s\n", a);
    close(fd);
}
