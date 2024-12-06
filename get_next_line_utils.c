/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:12:58 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/06 22:06:44 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*open_file(const char *filename)
{
	int		fd;
	t_file	*file;

	fd = open(filename, O_RDONLY);
	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (file);
	file->fd = fd;
	file->bytes_read = 0;
	return (file);
}

void	close_file(t_file *file)
{
	close(file->fd);
	free(file);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	count;
	size_t	length;
	size_t	dest_length;
	size_t	src_length;

	count = 0;
	length = ft_strlen(dest);
	dest_length = ft_strlen(dest);
	src_length = ft_strlen(src);
	// int tmp = src[size - dest_length - 2] != '\n';
	// size += tmp;
	if (size <= dest_length)
		return (size + src_length);
	while (src[count] && count < size - dest_length - 1)
	{
		dest[length + count] = src[count];
		src[count] = 0;
		count++;
	}
	dest[length + count] = '\0';
	return (length + count);
}


void	*ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = s;
	while (i < n)
		dest[i++] = 0;
	return (dest);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
