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
# include  "get_next_line.h"
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
/*
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
}*/

char	*ft_strjoin(char  *s1, char  *s2)
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
    while (*buffer)
    {
        if (*buffer == '\n')
            return (1);
        buffer++;
		printf("%d\n", 33);
    }
    return (0);
}

static char *get_buffer(int fd)
{
    char    *buffer;


    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return(NULL);
    if (read(fd, buffer, BUFFER_SIZE) < 0)
	{
		free(buffer);
        return (NULL);
	}
	buffer[BUFFER_SIZE] = '\0';
    return (buffer);
}

int	output_len(char *str)
{
	int	len;
	
	len = 0;
	while (*str != '\n' && str)
    {
        str++;
		len++;
    }
    return (len);
}

char	*get_output(char *str)
{
	char	*output;
	int		len;
	int		i;

	len = output_len(str);
	printf("%d\n", len);
	i = 0;
	output = malloc(len + 1);
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

int	left_len(char *str)
{
	int	len;
	
	len = 0;
	while (*str != '\n')
        str++;
	while (*str)
	{
		str++;
		len++;
	}
    return (len);
}

char	*get_left(char	*str)
{
	char	*left;
	int		llen;
	int		olen;
	int		i;

	i = 0;
	llen = left_len(str);
	olen = output_len(str);
	left = malloc(llen + 1);
	while (str[olen - 1])
	{
		left[i] = str[olen + 1];
		olen++;
		i++;
	}
	free (str);
	left[i] = '\0';
	return (left);

}

char    *get_next_line(int fd)
{
    static char    *line;
    char    *temp;
	char	*joined;
	char	*output;

	if (output)
		free((void *) output);
    if (!line)
	{
		line = get_buffer(fd);
	}
	printf("%d\n", 1);
	while (check_buffer(line) != 1)
	{
		temp = get_buffer(fd);
		joined = ft_strjoin(line, temp);
		free((void *)temp);
		free((void *)line);
		line = joined;
	}
	output = get_output(line);
	line = get_left(line);
    return (output);
}
//    line = ft_left(line);
//    return(ft_final_line(line));

int main(void)
{
    int		fd;
    char    *a;

    fd = open("prueba.txt", O_RDONLY);
	a = get_next_line(fd);
	printf("%s\n", a);
	free((void *)a);
	a = get_next_line(fd);
	printf("%s\n", a);
	free((void *)a);
	a = get_next_line(fd);
	printf("%s\n", a);
	free((void *)a);
	a = get_next_line(fd);
	printf("%s\n", a);
	free((void *)a);
    close(fd);
	return (0);
}
