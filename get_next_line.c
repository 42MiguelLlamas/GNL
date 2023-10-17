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

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	check = 1;
	while (check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check < 0)
		{
			free(buffer);
			free(left);
			left = NULL;
			return (NULL);
		}
		buffer[check] = '\0';
		temp = ft_strjoin(left, buffer);
		left = temp;
		if (ft_strchr(buffer, 10))
			break ;
	}
	free(buffer);
	if (check == 0 && left[0] == '\0')
	{
		free(left);
		return (NULL);
	}
//	printf("B-%s", left);
	return (left);
}

char	*get_output(char *str)
{
	char	*output;
	int		len;
	int		i;

	len = output_len(str);
	i = 0;
	output = malloc(len + 2);
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		output[i] = '\n';
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
	left = malloc(llen + 1);
	while (olen < len)
	{
		left[i] = str[olen + 1];
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
	if (!line)
		line = ft_calloc(1, 1);
	line = get_buffer(fd, line);
	if (line)
	{
		output = get_output(line);
		line = get_left(line);
		return (output);
	}
	return (NULL);
}
/*
int main(void)
{
    int fd;
    char *line;

    fd = open("prueba.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
	line = get_next_line(fd);
    printf("1%s", line);
	line = get_next_line(fd);
    printf("2%s", line);
    close(fd);
    fd = open("prueba.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
	line = get_next_line(fd);
    printf("1%s", line);
    return (0);
}*/
