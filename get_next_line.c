/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:12:50 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/06 22:07:48 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_realloc(char *ptr, size_t new_size)
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

char	*parse_line(char *s, t_file *file, int realloc, int buff_size)
{
	int		len;

	len = 0;
	if (buff_size == 1)
		return (file->line);
	if (!file->bytes_read)
		return (file->line = NULL);
	if ((file->bytes_parsed) == buff_size)
		file->bytes_parsed = 0;
	while (++file->bytes_parsed < buff_size && s[len] && s[len] != '\n')
		len++;
	if (realloc)
	{
		file->line_len = ft_strlen(file->line);
		file->line = ft_realloc(file->line, (len + file->line_len + 2));
		file->line_len = ft_strlcat(file->line, s, (len + file->line_len + 2));
	}
	else
	{
		file->line = (char *)ft_calloc(sizeof(char), (len + 2));
		*file->line = 0;
		if (!file->line)
			return (NULL);
		file->line_len = ft_strlcat(file->line, s, len + 2);
	}
	return (file->line);
}

int	is_empty(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size && !buffer[i])
		i++;
	return (!buffer[i]);
}

char	*get_next_line(int fd)
{
	static t_file	file = {
		.fd = -1,
		.line_len = 0,
		.bytes_read = 0,
		.bytes_parsed = 0,
		.line = NULL
	};
	int				empty;
	static char		buffer[BUFFER_SIZE + 1];

	if (fd != -1)
		file.fd = fd;
	else
		return (NULL);
	empty = is_empty(buffer, BUFFER_SIZE);
	if (empty)
		file.bytes_read = read(file.fd, buffer, BUFFER_SIZE);
	parse_line(&buffer[file.bytes_parsed], &file, 0, BUFFER_SIZE);
	while ((file.bytes_read == BUFFER_SIZE) && file.line
		&& file.line[file.line_len - 1] != '\n')
	{
		file.bytes_read = read(fd, buffer, BUFFER_SIZE);
		parse_line(buffer, &file, 1, BUFFER_SIZE);
	}
	return (file.line);
}

