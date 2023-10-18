/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:51:28 by mllamas-          #+#    #+#             */
/*   Updated: 2023/10/14 15:23:08 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
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

char	*ft_strchr(char *ptr, int c)
{
	char	a;
	int		num;

	num = 0;
	a = (char)c;
	while (*ptr != a && *ptr)
		ptr++;
	if (*ptr != a)
		return (0);
	return (ptr);
}

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((len + 1) * sizeof(char), 1);
	if (!str)
		ft_freeleft(&s1);
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
	free(s1);
	return (str);
}

int	output_len(char *str)
{
	int	len;

	len = 0;
	if (*str == '\n')
		return (0);
	while (*str != '\n' && *str)
	{
		str++;
		len++;
	}
	return (len);
}
