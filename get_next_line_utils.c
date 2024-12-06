/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:12:58 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/06 16:24:45 by chuezeri         ###   ########.fr       */
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
	if (size <= dest_length)
		return (size + src_length);
	while (src[count] && count < size - dest_length - 1)
	{
		dest[length + count] = src[count];
		src[count] = 0;
		count++;
	}
	dest[length + count] = '\0';
	return (dest_length + src_length);
}
