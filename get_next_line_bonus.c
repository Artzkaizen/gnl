/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:39:34 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/18 16:39:32 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_FD 1024

static char	*ft_realloc(char *ptr, size_t new_size)
{
	size_t	i;
	char	*new_ptr;

	if (!ptr)
		return ((char *)ft_calloc(new_size, (new_size / new_size)));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (char *)ft_calloc(new_size, (new_size / new_size));
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (ptr[i] && i < new_size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

static char	*parse_line(char *s, t_file *file, int realloc, int buff_size)
{
	int		len;

	len = 0;
	if (!file->bytes_read || !*s)
		return (file->line = NULL);
	if ((file->bytes_parsed) == buff_size)
		file->bytes_parsed = 0;
	while (++file->bytes_parsed < buff_size && s[len] && s[len] != '\n')
		len++;
	if (realloc)
	{
		file->line_len = ft_strlen(file->line);
		file->line = ft_realloc(file->line, (len + file->line_len + 2));
		len += file->line_len;
	}
	else
	{
		file->line = (char *)ft_calloc(sizeof(char), (len + 2));
		if (!file->line)
			return (NULL);
	}
	file->line_len = ft_strlcat(file->line, s, (len + 2));
	return (file->line);
}

static int	is_empty(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size && !buffer[i])
		i++;
	return (!buffer[i]);
}

char	*get_next_line(int fd)
{
	int				empty;
	static t_file	files[MAX_FD];

	// if (fd >= MAX_FD)
	// 	return (NULL);
	empty = is_empty(files[fd].buffer, BUFFER_SIZE);
	if (empty)
		files[fd].bytes_read = read(fd, files[fd].buffer, BUFFER_SIZE);
	if (files[fd].bytes_read == files[fd].bytes_parsed)
		files[fd].bytes_parsed = 0;
	parse_line(&files[fd].buffer[files[fd].bytes_read],
		&files[fd], 0, BUFFER_SIZE);
	while ((files[fd].bytes_read == BUFFER_SIZE) && files[fd].line
		&& files[fd].line[files[fd].line_len - 1] != '\n')
	{
		files[fd].bytes_read = read(fd, files[fd].buffer, BUFFER_SIZE);
		if (files[fd].bytes_read > 0)
			parse_line(files[fd].buffer, &files[fd], 1, BUFFER_SIZE);
	}
	return (files[fd].line);
}
