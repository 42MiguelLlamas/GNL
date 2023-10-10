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

static size_t ft_byte_len(int fd)
{
    char    a;
    size_t  count;

    count = 0;
    while (read(fd, &a, 1) > 0 && a != '\n')
        count++;
    if (read(fd, &a, 1) < 0)
        return (0);
    return (count);
}

char    *get_next_line(int fd)
{
    size_t  bytes;
    char    *buffer;

    bytes = ft_byte_len(fd);
    if (bytes == 0)
        return (NULL);
    buffer = ft_calloc(bytes, sizeof(char));
    if (!buffer)
        return (NULL);
    return ("a");
}

int main(void)
{
    int fd;
    char    *a;

    fd = open("prueba.txt", O_RDONLY);
    a = get_next_line(fd);
    close(fd);
}
