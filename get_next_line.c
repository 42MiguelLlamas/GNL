/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:30:41 by mllamas-          #+#    #+#             */
/*   Updated: 2023/10/14 15:17:57 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


static char	*get_buffer(int fd, char *left)
{
	char	*buffer;
	char	*temp;
	int		check;

	if (!left)
		left = ft_calloc(1,1);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	check = 1;
	while(check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[BUFFER_SIZE] = '\0';
		temp = ft_strjoin(left, buffer);
		free(left);
		left = temp;
		if (ft_strchr(buffer, 10))
			break;
	}
	free(buffer);
	return (left);
}

char	*get_output(char *str)
{
	char	*output;
	int		len;
	int		i;

	len = output_len(str);
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


char	*get_left(char	*str)
{
	char	*left;
	int		llen;
	int		olen;
	int		len;
	int		i;

	i = 0;
	olen = output_len(str);
	len = ft_strlen(str);
	llen = len - olen;
	left = ft_calloc(llen + 1, 1);
	while (olen < len)
	{
		left[i] = str[olen];
		i++;
		olen++;
	}
	left[i] = '\0';
	free(str);
	return (left);
}


char	*get_next_line(int fd)
{
	static char	*line;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = get_buffer(fd, line);
	if (!line)
		return (NULL);
	output = get_output(line);
	line = get_left(line);
	return (output);
}

int main(void)
{
    int		fd;
    char    *a;

    fd = open("prueba.txt", O_RDONLY);
	a = get_next_line(fd);
	printf("%s", a);
	a = get_next_line(fd);
	printf("%s", a);
	return (0);
}
